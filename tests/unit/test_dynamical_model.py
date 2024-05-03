import numpy as np

from symaware.simulators.prescan import (
    AmesimDynamicalModel,
    CustomDynamicalModel,
    DynamicalModel,
    Gear,
    TrackModel,
)
from symaware.simulators.prescan._symaware_prescan import (
    _AmesimDynamicalModel,
    _CustomDynamicalModel,
    _TrackModel,
)


class TestAmesimDynamicalModel:

    def test_amesim_dynamical_model_init(self):
        ID = 1
        model = AmesimDynamicalModel(ID)
        assert isinstance(model, DynamicalModel)
        assert model.id == ID
        assert np.array_equal(model.control_input, np.zeros(4))
        assert isinstance(model.internal_model, _AmesimDynamicalModel)
        assert model.subinputs_dict == {
            "throttle": 0,
            "brake": 0,
            "steering_wheel_angle": 0,
            "gear": Gear.Neutral,
        }


class TestCustomDynamicalModel:

    def test_custom_dynamical_model_init(self):
        ID = 2
        model = CustomDynamicalModel(ID)
        assert isinstance(model, DynamicalModel)
        assert model.id == ID
        assert np.array_equal(model.control_input, np.zeros(15))
        assert isinstance(model.internal_model, _CustomDynamicalModel)
        assert model.subinputs_dict.keys() == {
            "position",
            "orientation",
            "acceleration",
            "velocity",
            "angular_velocity",
        }


class TestTrackModel:

    def test_track_model_init(self):
        ID = 3
        model = TrackModel(ID)
        assert isinstance(model, DynamicalModel)
        assert model.id == ID
        assert np.array_equal(model.control_input, np.zeros(0))
        assert isinstance(model.internal_model, _TrackModel)
        assert not model.subinputs_dict
