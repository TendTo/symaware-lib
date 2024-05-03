# pylint: disable=missing-function-docstring, missing-class-docstring, no-self-use
import numpy as np

from symaware.simulators.prescan import BoxEntity
from symaware.simulators.prescan.prescan import SensorDetectability


class TestBoxEntity:

    def test_box_entity_init(self):
        entity = BoxEntity()
        assert np.array_equal(entity.position, np.array([0, 0, 0]))
        assert np.array_equal(entity.orientation, np.array([0, 0, 0]))
        assert np.array_equal(entity.cog_offset, np.array([0, 0, 0]))
        assert entity.is_collision_detectable
        assert entity.is_movable
        assert entity.sensor_detectability == SensorDetectability.SensorDetectabilityDetectable

    def test_box_entity_init_custom(self):
        entity = BoxEntity(
            position=np.array([1, 2, 3]),
            orientation=np.array([4, 5, 6]),
            cog_offset=np.array([7, 8, 9]),
            is_collision_detectable=False,
            is_movable=False,
            sensor_detectability=SensorDetectability.SensorDetectabilityInvisible,
        )
        assert np.array_equal(entity.position, np.array([1, 2, 3]))
        assert np.array_equal(entity.orientation, np.array([4, 5, 6]))
        assert np.array_equal(entity.cog_offset, np.array([7, 8, 9]))
        assert not entity.is_collision_detectable
        assert not entity.is_movable
        assert entity.sensor_detectability == SensorDetectability.SensorDetectabilityInvisible
