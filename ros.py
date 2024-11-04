import os

import numpy as np

from symaware.base import (
    Agent,
    AgentCoordinator,
    AwarenessVector,
    Controller,
    KnowledgeDatabase,
    MultiAgentAwarenessVector,
    MultiAgentKnowledgeDatabase,
    TimeIntervalAsyncLoopLock,
    TimeSeries,
    initialize_logger,
    PerceptionSystem,
)

PRESCAN_DIR = "C:/Program Files/Simcenter Prescan/Prescan_2403"  # Adjust if needed
os.add_dll_directory(f"{PRESCAN_DIR}/bin")
os.environ["PATH"] = f"{PRESCAN_DIR}/bin;{os.environ['PATH']}"

try:
    from symaware.simulators.prescan import (
        AirSensor,
        CustomDynamicalModel,
        Entity,
        Environment,
        ExistingEntity,
        Pose,
        TrackModel,
        DeerEntity,
    )
except ImportError as e:
    raise ImportError(
        "symaware-pybullet non found. "
        "Try running `pip install symaware-pybullet` or `pip install symaware[simulators]`"
    ) from e

try:
    from symaware.extra.ros import (
        RosClient,
        RosCommunicationReceiver,
        RosCommunicationSender,
        PrescanStatus,
        Path,
        AirSensorOutput,
        PoseStamped,
        Point,
        Quaternion,
        Pose as RosPose,
        RosMessage,
    )

except ImportError as e:
    raise ImportError(
        "symaware-ros non found. " "Try running `pip install symaware-ros` or `pip install symaware[ros]`"
    ) from e


ROS_MASTER_HOST = "139.19.164.117"
PATH_TOPIC = "path"
PRESCAN_STATUS_TOPIC = "/prescan_status"
AIR_SENSOR_OUTPUT_TOPIC = "air_sensor_output"
CONTROL_INPUT_TOPIC = "control_input"
TRAFFIC_LIGHTS_TOPIC = "traffic_lights"
POSE_TOPIC = "pose"

nan_array = np.nan * np.empty(9)


class MyKnowledgeDatabase(KnowledgeDatabase):
    pose: Pose


def quaternion_from_euler(roll: float, pitch: float, yaw: float, degrees=False):
    if degrees:
        deg2rad = np.pi / 180
        roll *= deg2rad
        pitch *= deg2rad
        yaw *= deg2rad

    cy = np.cos(yaw * 0.5)
    sy = np.sin(yaw * 0.5)
    cr = np.cos(roll * 0.5)
    sr = np.sin(roll * 0.5)
    cp = np.cos(pitch * 0.5)
    sp = np.sin(pitch * 0.5)

    w = cy * cr * cp + sy * sr * sp
    x = cy * sr * cp - sy * cr * sp
    y = cy * cr * sp + sy * sr * cp
    z = sy * cr * cp - cy * sr * sp

    return np.array([x, y, z, w])


def quaternion_to_euler(x: float, y: float, z: float, w: float, degrees=False):
    if degrees:
        deg = 180 / np.pi
    else:
        deg = 1

    sinr_cosp = 2 * (w * x + y * z)
    cosr_cosp = 1 - 2 * (x * x + y * y)
    roll = np.arctan2(sinr_cosp, cosr_cosp) * deg
    sinp = 2 * (w * y - z * x)
    pitch = np.arcsin(sinp) * deg
    siny_cosp = 2 * (w * z + x * y)
    cosy_cosp = 1 - 2 * (y * y + z * z)
    yaw = np.arctan2(siny_cosp, cosy_cosp) * deg

    return roll, pitch, yaw


class PoseStampedRosCommunicationReceiver(RosCommunicationReceiver):

    def __init__(
        self,
        agent_id,
        compression=None,
        throttle_rate=0,
        queue_size=100,
        queue_length=0,
        reconnect_on_close=True,
        async_loop_lock=None,
    ):
        super().__init__(
            agent_id,
            f"/car_{agent_id}/{POSE_TOPIC}",
            PoseStamped,
            compression,
            throttle_rate,
            queue_size,
            queue_length,
            reconnect_on_close,
            async_loop_lock,
        )

    def _decode_message(self, *messages: RosMessage) -> Pose:
        for message in messages:
            data: PoseStamped = message.data
            pos = data.pose.position
            ori = data.pose.orientation
            rpy = quaternion_to_euler(ori.x, ori.y, ori.z, ori.w)
            return Pose(x=pos.x * 10, y=pos.y * 10, z=pos.z + 0.4, roll=rpy[0], pitch=rpy[1], yaw=rpy[2])
        return Pose(False)

    def _update(self, pose: Pose):
        self._agent.self_knowledge["pose"] = pose


class CarAirSensor(PerceptionSystem):
    def __init__(self, agent_id, async_loop_lock=None):
        super().__init__(agent_id, async_loop_lock)
        self.__air: AirSensor
        self.__air_publisher: RosCommunicationSender

    def initialise_component(self, agent, initial_awareness_database, initial_knowledge_database):
        super().initialise_component(agent, initial_awareness_database, initial_knowledge_database)
        assert isinstance(self._agent.entity, Entity)
        self.__air = self._agent.entity.get_sensor_of_type(AirSensor)
        self.__air_publisher = next(
            filter(
                lambda c: isinstance(c, RosCommunicationSender) and c.topic.endswith("air_sensor_output"),
                self._agent.components,
            )
        )

    def _compute(self) -> tuple[np.ndarray, TimeSeries]:
        # data = json.dumps({"id": str(self._agent_id), "position": [-1.7422, 1.6658, 0.0000], "status": "red"})
        if len(self.__air.data) == 0:
            data = AirSensorOutput(range=999999)
        else:
            data = AirSensorOutput(
                tid=str(self.__air.target_id),
                range=self.__air.range,
                velocity=self.__air.velocity,
                azimuth=self.__air.azimuth,
                heading=self.__air.heading,
            )
        self.__air_publisher.enqueue_messages(RosMessage(sender_id=self._agent.id, receiver_id=-1, data=data))

    def _update(self, _):
        pass


class CarController(Controller):
    def _compute(self) -> tuple[np.ndarray, TimeSeries]:
        pose: Pose = self._agent.self_knowledge["pose"]
        return np.concatenate((np.array(pose), nan_array)), TimeSeries()


class TrafficLightController(Controller):

    def __init__(self, agent_id: int, async_loop_lock=None):
        super().__init__(agent_id, async_loop_lock)

    def initialise_component(
        self,
        agent: Agent,
        initial_awareness_database: MultiAgentAwarenessVector,
        initial_knowledge_database: "MultiAgentKnowledgeDatabase[MyKnowledgeDatabase]",
    ):
        super().initialise_component(agent, initial_awareness_database, initial_knowledge_database)
        assert isinstance(self._agent.entity, Entity)
        self.__air: AirSensor = self._agent.entity.get_sensor_of_type(AirSensor)
        # self.__lms: LmsSensor = self._agent.entity.get_sensor_of_type(LmsSensor)

    def _compute(self, compute_control_input: bool = False) -> tuple[np.ndarray, TimeSeries]:
        # return np.array([1, 0, 0, Gear.Forward]), TimeSeries()
        pose: Pose = self._agent.self_knowledge["pose"]
        # return np.array([0, 0, 0, 0, min(counter, 1), 0]), TimeSeries()
        # return np.array([1, 0, 0, Gear.Forward]), TimeSeries()
        return np.concatenate((np.array(pose), nan_array)), TimeSeries()


def main():

    ###########################################################
    # 0. Parameters                                           #
    ###########################################################
    TIME_INTERVAL = 0.05
    LOG_LEVEL = "INFO"  # Among DEBUG, INFO, WARNING, ERROR, CRITICAL
    NUM_PATH_SEGMENTS = 500
    # Any arbitrary number will work, as long as there are no other entities with the same ID
    PEDESTRIAN_1_ID = 21
    PEDESTRIAN_2_ID = 22
    AGENT_ID = 3

    initialize_logger(LOG_LEVEL)

    ###########################################################
    # Load the environment from the file and add entities     #
    ###########################################################
    env = Environment(filename="PrescanDemoAMC.pb", async_loop_lock=TimeIntervalAsyncLoopLock(TIME_INTERVAL))
    env.add_entities(DeerEntity(position=np.array([0, -14, 0]), orientation=np.array((0, 0, -90))))

    traffic_light_1 = env.add_entities(ExistingEntity(id=1, object_name="RoadsideLight_NL_1"))
    traffic_light_2 = env.add_entities(ExistingEntity(id=2, object_name="RoadsideLight_NL_2"))

    ###########################################################
    # Create, initialise and add pedestrians to the env       #
    ###########################################################
    pedestrian_1 = Agent(
        PEDESTRIAN_1_ID,
        entity=ExistingEntity(
            id=PEDESTRIAN_1_ID, object_name="Female_Regular_1", model=TrackModel(PEDESTRIAN_2_ID, existing=True)
        ),
    )
    pedestrian_2 = Agent(
        PEDESTRIAN_2_ID,
        entity=ExistingEntity(
            id=PEDESTRIAN_2_ID, object_name="Female_Regular_2", model=TrackModel(PEDESTRIAN_2_ID, existing=True)
        ),
    )

    pedestrian_1.initialise_agent(
        AwarenessVector(pedestrian_1.id, np.zeros(8)), {pedestrian_1.id: MyKnowledgeDatabase()}
    )
    pedestrian_2.initialise_agent(
        AwarenessVector(pedestrian_2.id, np.zeros(8)), {pedestrian_2.id: MyKnowledgeDatabase()}
    )

    env.add_agents(pedestrian_1, pedestrian_2)

    ###########################################################
    # Add the car to the environment                          #
    ###########################################################
    agent_entity = ExistingEntity(
        id=AGENT_ID,
        object_name="Ford_Fiesta_Hatchback_1",
        sensors=(AirSensor(existing=True)),
        model=CustomDynamicalModel(AGENT_ID),
    )
    agent = Agent[MyKnowledgeDatabase](AGENT_ID, agent_entity)
    env.add_agents(agent)

    track_model = TrackModel(AGENT_ID, existing=True, active=False)
    track_model.link_entity(agent_entity)
    env.add_models(track_model)

    ###########################################################
    # Create and set the component of the agent               #
    ###########################################################
    status_publisher = RosCommunicationSender(agent.id, topic=PRESCAN_STATUS_TOPIC, message_type=PrescanStatus)
    path_publisher = RosCommunicationSender(agent.id, topic=f"/car_{agent.id}/{PATH_TOPIC}", message_type=Path)
    air_publisher = RosCommunicationSender(
        agent.id, topic=f"/car_{agent.id}/{AIR_SENSOR_OUTPUT_TOPIC}", message_type=AirSensorOutput
    )

    pose_subscriber = PoseStampedRosCommunicationReceiver(agent.id)
    agent.add_components(
        CarController(agent.id, TimeIntervalAsyncLoopLock(TIME_INTERVAL)),
        CarAirSensor(agent.id, TimeIntervalAsyncLoopLock(TIME_INTERVAL)),
        status_publisher,
        path_publisher,
        pose_subscriber,
        air_publisher,
    )

    ###########################################################
    # Initialise the agent with some starting information     #
    ###########################################################
    awareness_vector = AwarenessVector(agent.id, np.zeros(8))
    knowledge_database = MyKnowledgeDatabase(pose=Pose(False))
    agent.initialise_agent(awareness_vector, {agent.id: knowledge_database})

    ###########################################################
    # Run the simulation                                      #
    ###########################################################
    def post_init(_: AgentCoordinator):
        path_msg = Path()
        for pose in track_model.trajectory_poses(NUM_PATH_SEGMENTS):
            quaternion = quaternion_from_euler(pose[3], pose[4], pose[5])
            path_msg.poses.append(RosPose(position=Point(*(pose[:3] / 10.0)), orientation=Quaternion(*quaternion)))
        path_publisher.enqueue_messages(RosMessage(sender_id=agent.id, receiver_id=-1, data=path_msg))
        status_publisher.enqueue_messages(
            RosMessage(sender_id=agent.id, receiver_id=-1, data=PrescanStatus(ready=True))
        )

    agent_coordinator = AgentCoordinator[MyKnowledgeDatabase](env, post_init=post_init)

    agent_coordinator.add_agents(agent, pedestrian_1, pedestrian_2)

    agent_coordinator.run(TIME_INTERVAL, timeout=17)

    RosClient.publish_topic(PRESCAN_STATUS_TOPIC, PrescanStatus.msg_type()).publish(PrescanStatus(stop=True).to_dict())

    print("Closing...")


if __name__ == "__main__":
    with RosClient(host=ROS_MASTER_HOST):
        main()
