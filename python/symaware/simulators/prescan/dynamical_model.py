from typing import TypedDict

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
        self._entity_id = -1
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
        self._internal_model.initialise_object(experiment, obj)

    def step(self, simulation: _ISimulation):
        self._internal_model.step(simulation)


class AmesimDynamicalModel(DynamicalModel):
    """
    Prescan dynamical model based on an AMESim model.

    Args
    ----
    ID:
        Identifier of the agent this model belongs to
    """

    def __init__(self, ID: Identifier):
        super().__init__(ID, control_input=np.zeros(4))
        self._internal_model = _AmesimDynamicalModel()

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
    """

    def __init__(self, ID: Identifier):
        super().__init__(ID, control_input=np.zeros(15))
        self._internal_model = _CustomDynamicalModel()

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
    """

    def __init__(self, ID: Identifier):
        super().__init__(ID, control_input=np.zeros(0))
        self._internal_model = _TrackModel()

    @property
    def subinputs_dict(self) -> TrackModelInput:
        return {}
