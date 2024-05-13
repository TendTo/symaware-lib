from abc import ABC, abstractmethod
from dataclasses import dataclass

import numpy as np

from ._symaware_prescan import SensorType, _Sensor


@dataclass(frozen=True, init=False)
class Sensor(ABC):
    """
    Abstract class for a sensor in the Pescan simulator.
    Interacting with the Prescan simulator is delegated to the _internal_sensor object, which is an instance of _Sensor.

    Note
    ----
    Do not manipulate the _internal_sensor object directly.
    """

    existing: bool = False
    _internal_sensor: _Sensor = None  # type: ignore

    def __init__(self, setup: "np.ndarray | None" = None, existing: bool = False):
        object.__setattr__(self, "existing", existing)
        internal_sensor = (
            _Sensor(self.sensor_type, self.existing)
            if setup is None
            else _Sensor(self.sensor_type, setup, self.existing)
        )
        object.__setattr__(self, "_internal_sensor", internal_sensor)

    @property
    def setup(self) -> np.ndarray:
        """Setup used in the creation of this sensor"""
        return np.array(self._internal_sensor.setup)

    @property
    @abstractmethod
    def sensor_type(self) -> SensorType:
        """Type of the sensor"""
        pass

    @property
    @abstractmethod
    def data(self) -> np.ndarray:
        """Data collected by the sensor"""
        pass


@dataclass(frozen=True, init=False)
class AirSensor(Sensor):
    """
    Air sensor in the Prescan simulator.
    """

    @property
    def sensor_type(self) -> SensorType:
        return SensorType.AIR

    @property
    def data(self) -> np.ndarray:
        """
        Data captured by the sensor.
        Structured as follows:

        - range
        - azimuth
        - elevation
        - target_id
        - velocity
        - heading
        """
        return np.array(self._internal_sensor.state)

    @property
    def range(self) -> float:
        return self._internal_sensor.state[0]

    @property
    def azimuth(self) -> float:
        return self._internal_sensor.state[1]

    @property
    def elevation(self) -> float:
        return self._internal_sensor.state[2]

    @property
    def target_id(self) -> int:
        return round(self._internal_sensor.state[3])

    @property
    def velocity(self) -> float:
        return self._internal_sensor.state[4]

    @property
    def heading(self) -> float:
        return self._internal_sensor.state[5]


@dataclass(frozen=True, init=False)
class BrsSensor(Sensor):
    """
    Brs sensor in the Prescan simulator.
    """

    @property
    def sensor_type(self) -> SensorType:
        return SensorType.BRS

    @property
    def data(self) -> np.ndarray:
        """
        Data captured by the sensor.
        Structured as follows:

        - target_id
        - left
        - right
        - bottom
        - top
        """
        return np.array(self._internal_sensor.state)

    @property
    def target_id(self) -> int:
        return round(self._internal_sensor.state[0])

    @property
    def left(self) -> float:
        return self._internal_sensor.state[1]

    @property
    def right(self) -> float:
        return self._internal_sensor.state[2]

    @property
    def bottom(self) -> float:
        return self._internal_sensor.state[3]

    @property
    def top(self) -> float:
        return self._internal_sensor.state[4]


@dataclass(frozen=True, init=False)
class LmsSensor(Sensor):
    """
    Lms sensor in the Prescan simulator.
    """

    @dataclass(frozen=True)
    class LmsLine:
        x: float
        y: float
        z: float
        curvature: float

    @property
    def sensor_type(self) -> SensorType:
        return SensorType.LMS

    @property
    def data(self) -> np.ndarray:
        """
        Data captured by the sensor.
        Structured as a linearized array of lms lines, where each line is structured as follows:

        - x
        - y
        - z
        - curvature
        """
        return np.array(self._internal_sensor.state)

    @property
    def lms_lines(self) -> tuple[LmsLine]:
        """Tuple of lms lines detected by the sensor"""
        return tuple(
            LmsSensor.LmsLine(*self._internal_sensor.state[i : i + 4])
            for i in range(0, len(self._internal_sensor.state), 4)
        )

    def get_lms_line(self, i: int) -> float:
        """
        Get the i-th lms line

        Args
        ----
        i:
            index of the line to get

        Returns
        -------
            i-th lms line

        Raises
        ------
        IndexError: if i is out of bounds
        """
        return LmsSensor.LmsLine(*self._internal_sensor.state[i * 4 : i * 4 + 4])

    def get_x(self, i: int) -> float:
        """
        Get the x value of the i-th lms line

        Args
        ----
        i:
            index of the line to get the x value from

        Returns
        -------
            x value of the i-th lms line

        Raises
        ------
        IndexError: if i is out of bounds
        """
        return self._internal_sensor.state[i * 4]

    def get_y(self, i: int) -> float:
        """
        Get the y value of the i-th lms line

        Args
        ----
        i:
            index of the line to get the y value from

        Returns
        -------
            y value of the i-th lms line

        Raises
        ------
        IndexError: if i is out of bounds
        """
        return self._internal_sensor.state[i * 4 + 1]

    def get_z(self, i: int) -> float:
        """
        Get the z value of the i-th lms line

        Args
        ----
        i:
            index of the line to get the z value from

        Returns
        -------
            z value of the i-th lms line

        Raises
        ------
        IndexError: if i is out of bounds
        """
        return self._internal_sensor.state[i + 4 + 2]

    def get_curvature(self, i: int) -> float:
        """
        Get the curvature of the i-th lms line

        Args
        ----
        i:
            index of the line to get the curvature from

        Returns
        -------
            curvature value of the i-th lms line

        Raises
        ------
        IndexError: if i is out of bounds
        """
        return self._internal_sensor.state[i * 4 + 3]
