import os

import numpy as np
import time
from dataclasses import dataclass
import json

from symaware.base import (
    Agent,
    AgentCoordinator,
    AwarenessVector,
    Controller,
    DefaultPerceptionSystem,
    KnowledgeDatabase,
    CommunicationReceiver,
    MultiAgentAwarenessVector,
    MultiAgentKnowledgeDatabase,
    TimeIntervalAsyncLoopLock,
    TimeSeries,
    get_logger,
    initialize_logger,
    CommunicationSender,
    Message as BaseMessage,
    Identifier,
    Tasynclooplock,
    PerceptionSystem,
)

import roslibpy
from typing import TypedDict

PRESCAN_DIR = "C:/Program Files/Simcenter Prescan/Prescan_2403"  # Adjust if needed
os.add_dll_directory(f"{PRESCAN_DIR}/bin")
os.environ["PATH"] = f"{PRESCAN_DIR}/bin;{os.environ['PATH']}"

try:
    from symaware.simulators.prescan import (
        AirSensor,
        AmesimDynamicalModel,
        CustomDynamicalModel,
        DeerEntity,
        Entity,
        Environment,
        ExistingEntity,
        Pose,
        Gear,
        LmsSensor,
        TrackModel,
        RoadsideLightNLEntity,
    )
except ImportError as e:
    raise ImportError(
        "symaware-pybullet non found. "
        "Try running `pip install symaware-pybullet` or `pip install symaware[simulators]`"
    ) from e


class MyKnowledgeDatabase(KnowledgeDatabase):
    pose: Pose


@dataclass(frozen=True)
class Message(BaseMessage):
    data: roslibpy.Message


class PointMessage(TypedDict):
    x: float
    y: float
    z: float


class QuaternionMessage(TypedDict):
    x: float
    y: float
    z: float
    w: float


class PoseMessage(TypedDict):
    position: PointMessage
    orientation: QuaternionMessage


class StampMessage(TypedDict):
    secs: int
    nsecs: int


class HeaderMessage(TypedDict):
    seq: int
    stamp: StampMessage
    frame_id: str


class PoseStampedMessage(TypedDict):
    header: HeaderMessage
    pose: PoseMessage


class PathMessage(TypedDict):
    header: HeaderMessage
    poses: list[PoseStampedMessage]


nan_array = np.nan * np.empty(9)


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


class RosClient:
    _ros: "roslibpy.Ros | None" = None
    _publishers: list[roslibpy.Topic] = []
    _subscribers: list[roslibpy.Topic] = []

    def __init__(self, host: str = "localhost", port: int = 9090):
        self._host = host
        self._port = port
        self._ros: "roslibpy.Ros | None" = None

    def __enter__(self):
        RosClient._ros = roslibpy.Ros(host=self._host, port=self._port)
        RosClient._ros.run()
        assert RosClient._ros.is_connected, "Could not connect to ROS master"
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        if RosClient._ros is not None:
            assert RosClient._ros.is_connected, "ROS not connected"
            for publisher in RosClient._publishers:
                publisher.unadvertise()
            for subscriber in RosClient._subscribers:
                subscriber.unsubscribe()
            RosClient._ros.close()

    @classmethod
    def ros(cls):
        return cls._ros

    @classmethod
    def is_connected(cls):
        return cls._ros is not None and cls._ros.is_connected

    @classmethod
    def publish_topic(cls, topic_name: str, message_type: str, latch: bool = False):
        assert cls._ros is not None, "ROS not connected"
        topic = roslibpy.Topic(cls._ros, topic_name, message_type, latch=latch)
        topic.advertise()
        cls._publishers.append(topic)
        return topic

    @classmethod
    def subscribe_topic(cls, topic_name: str, message_type: str, latch: bool = False):
        assert cls._ros is not None, "ROS not connected"
        topic = roslibpy.Topic(cls._ros, topic_name, message_type, latch=latch)
        cls._subscribers.append(topic)
        return topic

    def close(self):
        self.__exit__(None, None, None)


class RosPublisher(CommunicationSender):

    def __init__(
        self,
        agent_id: Identifier,
        topic_name: str,
        message_type: str,
        async_loop_lock: "Tasynclooplock | None" = None,
        send_to_self: bool = False,
    ):
        super().__init__(agent_id, async_loop_lock, send_to_self)
        self._topic: "roslibpy.Topic"
        self._topic_name = topic_name
        self._message_type = message_type

    @property
    def topic_name(self):
        return self._topic_name

    @property
    def message_type(self):
        return self._message_type

    def initialise_component(self, agent, initial_awareness_database, initial_knowledge_database):
        super().initialise_component(agent, initial_awareness_database, initial_knowledge_database)
        self._topic = RosClient.publish_topic(self._topic_name, self._message_type, latch=True)

    def _send_communication_through_channel(self, msg: Message):
        assert RosClient.is_connected(), "ROS not connected"
        self._topic.publish(msg.data)


class RosSubscriber(CommunicationReceiver):

    def __init__(
        self,
        agent_id: Identifier,
        topic_name: str,
        message_type: str,
        async_loop_lock: "Tasynclooplock | None" = None,
    ):
        super().__init__(agent_id, async_loop_lock)
        self._queue: list[PoseStampedMessage] = []
        self._topic: "roslibpy.Topic"
        self._topic_name = topic_name
        self._message_type = message_type

    @property
    def topic_name(self):
        return self._topic_name

    @property
    def message_type(self):
        return self._message_type

    def initialise_component(self, agent, initial_awareness_database, initial_knowledge_database):
        super().initialise_component(agent, initial_awareness_database, initial_knowledge_database)
        self._topic = RosClient.subscribe_topic(self._topic_name, self._message_type)
        self._topic.subscribe(lambda msg: self._queue.append(msg))

    def _decode_message(self, messages: tuple[PoseStampedMessage]) -> Pose:
        for message in messages:
            pos = message["pose"]["position"]
            ori = message["pose"]["orientation"]
            rpy = quaternion_to_euler(ori["x"], ori["y"], ori["z"], ori["w"])
            return Pose(x=pos["x"] * 10, y=pos["y"] * 10, z=pos["z"] + 0.4, roll=rpy[0], pitch=rpy[1], yaw=rpy[2])
        return Pose(False)

    def _update(self, pose: Pose):
        self._agent.self_knowledge["pose"] = pose

    def _receive_communication_from_channel(self) -> tuple[PoseStampedMessage]:
        old_queue = self._queue
        self._queue = []
        return old_queue


class PedestrianController(Controller):

    def __init__(self, agent_id, delay=0, async_loop_lock=None):
        super().__init__(agent_id, async_loop_lock)
        self._delay = delay
        self.start_time = 0

    def _compute(self) -> tuple[np.ndarray, TimeSeries]:
        assert isinstance(self._agent.model, TrackModel)
        if time.time() - self.start_time < self._delay:
            return self._agent.model.control_input_to_array(distance_multiplier=0), TimeSeries()
        return self._agent.model.control_input_to_array(distance_multiplier=1), TimeSeries()


class CarAirSensor(PerceptionSystem):
    def __init__(self, agent_id, async_loop_lock=None):
        super().__init__(agent_id, async_loop_lock)
        self.__air: AirSensor
        self.__air_publisher: RosPublisher

    def initialise_component(self, agent, initial_awareness_database, initial_knowledge_database):
        super().initialise_component(agent, initial_awareness_database, initial_knowledge_database)
        assert isinstance(self._agent.entity, Entity)
        self.__air = self._agent.entity.get_sensor_of_type(AirSensor)
        self.__air_publisher = next(
            filter(lambda c: isinstance(c, RosPublisher) and c.topic_name.endswith("sensor"), self._agent.components)
        )

    def _compute(self) -> tuple[np.ndarray, TimeSeries]:
        # data = json.dumps({"id": str(self._agent_id), "position": [-1.7422, 1.6658, 0.0000], "status": "red"})
        if len(self.__air.data) == 0:
            return
        data = json.dumps(
            {
                "id": f"pd_{int(self.__air.target_id)}",
                "range": self.__air.range / 10,
                "vel": self.__air.velocity / 10,
                "theta": self.__air.azimuth,
                "heading": self.__air.heading,
            }
        )
        self.__air_publisher.enqueue_messages(
            Message(sender_id=self._agent.id, receiver_id=-1, data=roslibpy.Message({"data": data}))
        )

    def _update(self, _):
        pass


class CarController(Controller):
    def _compute(self) -> tuple[np.ndarray, TimeSeries]:
        pose: Pose = self._agent.self_knowledge["pose"]
        return np.concatenate((np.array(pose), nan_array)), TimeSeries()


class TrafficLightController(Controller):

    def __init__(self, agent_id: int, async_loop_lock=None):
        super().__init__(agent_id, async_loop_lock)
        self.__air: AirSensor
        # self.__lms: LmsSensor

    def initialise_component(
        self,
        agent: Agent,
        initial_awareness_database: MultiAgentAwarenessVector,
        initial_knowledge_database: MultiAgentKnowledgeDatabase[MyKnowledgeDatabase],
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
    ROS_MASTER_HOST = "139.19.164.73"
    # Any arbitrary number will work, as long as there are no other entities with the same ID
    PEDESTRIAN_1_ID = 21
    PEDESTRIAN_2_ID = 22
    AGENT_ID = 3

    initialize_logger(LOG_LEVEL)

    ###########################################################
    # Load the environment from the file and add entities     #
    ###########################################################
    env = Environment(filename="PrescanDemoAMC.pb", async_loop_lock=TimeIntervalAsyncLoopLock(TIME_INTERVAL))
    # env.add_entities(DeerEntity(position=np.array([0, -14, 0]), orientation=np.array((0, 0, -90))))

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
    pedestrian_1.add_components(PedestrianController(pedestrian_1.id, delay=15))
    pedestrian_2.add_components(PedestrianController(pedestrian_2.id, delay=5))

    pedestrian_1.initialise_agent(
        AwarenessVector(pedestrian_1.id, np.zeros(8)), {pedestrian_1.id: MyKnowledgeDatabase()}
    )
    pedestrian_2.initialise_agent(
        AwarenessVector(pedestrian_2.id, np.zeros(8)), {pedestrian_2.id: MyKnowledgeDatabase()}
    )

    env.add_agents((pedestrian_1, pedestrian_2))

    ###########################################################
    # 2. Add the agent in the environment                     #
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
    # 3. Create and set the component of the agent            #
    ###########################################################
    with RosClient(ROS_MASTER_HOST):
        status_publisher = RosPublisher(
            agent.id,
            topic_name="/status",
            message_type="std_msgs/Bool",
            async_loop_lock=TimeIntervalAsyncLoopLock(TIME_INTERVAL),
        )
        path_publisher = RosPublisher(
            agent.id,
            topic_name=f"/car_{agent.id}/path",
            message_type="nav_msgs/Path",
            async_loop_lock=TimeIntervalAsyncLoopLock(TIME_INTERVAL),
        )
        air_publisher = RosPublisher(
            agent.id,
            topic_name=f"/car_{agent.id}/sensor",
            message_type="std_msgs/String",
            async_loop_lock=TimeIntervalAsyncLoopLock(TIME_INTERVAL),
        )
        pose_subscriber = RosSubscriber(
            agent.id,
            topic_name=f"/vrpn_client_node/Car_{agent.id}_Tracking/pose",
            message_type="geometry_msgs/PoseStamped",
            async_loop_lock=TimeIntervalAsyncLoopLock(TIME_INTERVAL),
        )
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
            header_msg = HeaderMessage(
                seq=0, stamp=StampMessage(secs=int(time.time()), nsecs=0), frame_id="f1Tenth_base"
            )
            poses_msg = []
            for pose in track_model.trajectory_poses(NUM_PATH_SEGMENTS):
                quaternion = quaternion_from_euler(pose[3], pose[4], pose[5])
                pose_msg = PoseMessage(
                    position=PointMessage(x=pose[0] / 10, y=pose[1] / 10, z=pose[2]),
                    orientation=QuaternionMessage(x=quaternion[0], y=quaternion[1], z=quaternion[2], w=quaternion[3]),
                )
                poses_msg.append(PoseStampedMessage(header=header_msg, pose=pose_msg))
            path = PathMessage(header=header_msg, poses=poses_msg)
            path_publisher.enqueue_messages(Message(sender_id=agent.id, receiver_id=-1, data=roslibpy.Message(path)))
            status_publisher.enqueue_messages(
                Message(sender_id=agent.id, receiver_id=-1, data=roslibpy.Message({"data": True}))
            )

            pedestrian_1.controller.start_time = time.time()
            pedestrian_2.controller.start_time = time.time()

        agent_coordinator = AgentCoordinator[MyKnowledgeDatabase](env, post_init=post_init)

        agent_coordinator.add_agents((agent, pedestrian_1, pedestrian_2))

        agent_coordinator.run(TIME_INTERVAL, timeout=40)

        print("Closing...")


if __name__ == "__main__":
    main()
