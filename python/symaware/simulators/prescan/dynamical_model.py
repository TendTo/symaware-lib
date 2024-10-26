from typing import TYPE_CHECKING, TypedDict

import numpy as np
from symaware.base.data import Identifier
from symaware.base.models import DynamicalModel as BaseDynamicalModel

from ._symaware_prescan import (
    _AmesimDynamicalModel,
    _CustomDynamicalModel,
    _EntityModel,
    _Experiment,
    _ISimulation,
    _TrackModel,
    _WorldObject,
)

if TYPE_CHECKING:
    # String type hinting to support python 3.9
    from ._symaware_prescan import (
        Acceleration,
        AngularVelocity,
        Gear,
        Orientation,
        Position,
        Velocity,
    )


class AmesimDynamicalModelInput(TypedDict):
    throttle: np.ndarray
    brake: np.ndarray
    steering_wheel_angle: np.ndarray
    gear: np.ndarray


class CustomDynamicalModelInput(TypedDict):
    position: np.ndarray
    orientation: np.ndarray
    acceleration: np.ndarray
    velocity: np.ndarray
    angular_velocity: np.ndarray


class TrackModelInput(TypedDict):
    pass


class DynamicalModel(BaseDynamicalModel):
    """
    Abstract class for the dynamical models using the Prescan simulator.

    Args
    ----
    ID:
        Identifier of the agent this model belongs to
    control_input:
        Initial control input of the agent. It also used to validate the size of future control inputs
    """

    def __init__(self, ID: Identifier, control_input: np.ndarray):
        super().__init__(ID, control_input=control_input)
        self._internal_model: _EntityModel

    @property
    def control_input(self) -> np.ndarray:
        return super().control_input

    @control_input.setter
    def control_input(self, value: np.ndarray):
        if not isinstance(value, np.ndarray):
            raise TypeError(f"Expected numpy array, got {type(value)}")
        if not value.shape == self.control_input_shape:
            raise ValueError(f"Expected numpy array of shape {self.control_input_shape}, got {value.shape}")
        self._control_input = value
        self._internal_model.set_input(self._control_input)  # type: ignore

    @property
    def internal_model(self) -> _EntityModel:
        return self._internal_model

    def initialise(self, experiment: _Experiment, obj: _WorldObject):
        self._internal_model.create_model(obj, experiment)

    def step(self, simulation: _ISimulation):
        self._internal_model.step(simulation)


class AmesimDynamicalModel(DynamicalModel):
    """
    Prescan dynamical model based on an AMESim model.

    Args
    ----
    ID:
        Identifier of the agent this model belongs to
    is_flat_ground:
        Whether to consider the ground as flat (more efficient) or not
    initial_velocity:
        Initial velocity of the entity
    existing:
        Whether the model is already present in the experiment or shall be created
    active:
        Whether the model will step in the simulation
    """

    def __init__(
        self,
        ID: Identifier,
        is_flat_ground: bool = True,
        initial_velocity: float = 0,
        existing: bool = False,
        active: bool = True,
    ):
        super().__init__(ID, control_input=np.zeros(4))
        self._internal_model = _AmesimDynamicalModel(
            _AmesimDynamicalModel.Setup(
                existing=existing, active=active, is_flat_ground=is_flat_ground, initial_velocity=initial_velocity
            )
        )

    def control_input_to_array(
        self, throttle: float, brake: float, steering_wheel_angle: float, gear: "Gear"
    ) -> np.ndarray:
        return np.array([throttle, brake, steering_wheel_angle, gear.value])

    @property
    def subinputs_dict(self) -> AmesimDynamicalModelInput:
        return {
            "throttle": self.control_input[0],
            "brake": self.control_input[1],
            "steering_wheel_angle": self.control_input[2],
            "gear": self.control_input[3],
        }


class CustomDynamicalModel(DynamicalModel):
    """
    Prescan dynamical model with a completely custom implementation.
    This model gives complete control over the state of the entity to the agent.
    It is advised to use this model only in conjunction with a physics engine.

    Args
    ----
    ID:
        Identifier of the agent this model belongs to
    active:
        Whether the model will step in the simulation
    """

    def __init__(self, ID: Identifier, existing: bool = False, active: bool = True):
        super().__init__(ID, control_input=np.zeros(15))
        self._internal_model = _CustomDynamicalModel(_CustomDynamicalModel.Setup(existing=existing, active=active))

    def control_input_to_array(
        self,
        position: "np.ndarray | Position",
        orientation: "np.ndarray | Orientation",
        acceleration: "np.ndarray | Acceleration",
        velocity: "np.ndarray | Velocity",
        angular_velocity: "np.ndarray | AngularVelocity",
    ) -> np.ndarray:
        if isinstance(position, np.ndarray):
            position = np.array(position)
        if isinstance(orientation, np.ndarray):
            orientation = np.array(orientation)
        if isinstance(acceleration, np.ndarray):
            acceleration = np.array(acceleration)
        if isinstance(velocity, np.ndarray):
            velocity = np.array(velocity)
        if isinstance(angular_velocity, np.ndarray):
            angular_velocity = np.array(angular_velocity)
        return np.concatenate((position, orientation, acceleration, velocity, angular_velocity))

    @property
    def subinputs_dict(self) -> CustomDynamicalModelInput:
        return {
            "position": self.control_input[:3],
            "orientation": self.control_input[3:7],
            "acceleration": self.control_input[7:10],
            "velocity": self.control_input[10:13],
            "angular_velocity": self.control_input[13:],
        }


class TrackModel(DynamicalModel):
    """
    Prescan dynamical model based on a track model.
    The entity will follow the track indicated by the model.
    No control input are allowed.

    Args
    ----
    ID:
        Identifier of the agent this model belongs to
    path:
        List of positions defining the track
    speed:
        Speed of the entity along the track
    tolerance:
        Tolerance of the entity to the track
    existing:
        Whether the model is already present in the experiment or shall be created
    active:
        Whether the model will step in the simulation
    """

    def __init__(
        self,
        ID: Identifier,
        path: "list[Position] | None" = None,
        speed: float = 0,
        tolerance: float = 0,
        existing: bool = False,
        active: bool = True,
    ):
        super().__init__(ID, control_input=np.array([1, 0, 1, 0, 1, 0]))
        self._internal_model = _TrackModel(
            _TrackModel.Setup(existing=existing, active=active, path=path or [], speed=speed, tolerance=tolerance)
        )

    def control_input_to_array(self, speed: float) -> np.ndarray:
        return np.array([speed])

    def trajectory_poses(self, num_segments: int) -> np.ndarray:
        """
        Get the poses of the trajectory followed by the entity.
        The poses are returned as a numpy array of shape (num_segments, 6), where each row is a pose
        and each column is a component of the pose (x, y, z, roll, pitch, yaw).

        Args
        ----
        num_segments:
            Number of segments to interpolate the trajectory

        Returns
        -------
            A list of num_segments poses along the trajectory
        """
        return self._internal_model.trajectory_poses(num_segments)

    @property
    def trajectory_positions(self) -> np.ndarray:
        return self._internal_model.trajectory_positions()

    @property
    def subinputs_dict(self) -> TrackModelInput:
        return {}
