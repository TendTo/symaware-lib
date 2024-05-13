import math
from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import TYPE_CHECKING

import numpy as np

from ._symaware_prescan import SensorType, _Sensor

if TYPE_CHECKING:
    from typing import Generator


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
        Structured as a linearized array of lms lines, where the readings for each line are structured as follows:

        - x
        - y
        - z
        - curvature

        The reading between each line are separated by a NaN value.

        Example
        -------
        >>> [1.02, 1.04, 1.35, 1.06,   1.03, 1.05, 1.36, 1.07, float("NaN"), 1.08, 1.09, 1.37, 1.10]
        >>> #l11x, l11y, l11z, l11c, | l12x, l12y, l12z, l12c,     ||        l21x, l21y, l21z, l21c
        """
        return np.array(self._internal_sensor.state)

    def _lms_line_generator(self, idx: int) -> "Generator[LmsSensor.LmsLine]":
        for i in range(idx, len(self._internal_sensor.state), 4):
            if math.isnan(self._internal_sensor.state[i]):
                return
            yield self.get_lms_line_reading(i)

    def _lms_lines_generator(self) -> "Generator[tuple[LmsSensor.LmsLine]]":
        i = 0
        while i < len(self._internal_sensor.state):
            lms_line = tuple(self._lms_line_generator(i))
            yield lms_line
            i += 1 + 4 * len(lms_line)

    @property
    def lms_lines(self) -> "tuple[tuple[LmsSensor.LmsLine]]":
        """List of lms lines detected by the sensor"""
        return tuple(self._lms_lines_generator())

    def get_lms_line_reading(self, i: int) -> float:
        """
        Get the lms reading starting ad index i.

        Args
        ----
        i:
            index of the line reading to get

        Returns
        -------
            lms line reading starting at index i

        Raises
        ------
        IndexError: if [ i : i + 4 ] is out of bounds
        """
        return LmsSensor.LmsLine(
            x=self._internal_sensor.state[i],
            y=self._internal_sensor.state[i + 1],
            z=self._internal_sensor.state[i + 2],
            curvature=self._internal_sensor.state[i + 3],
        )
