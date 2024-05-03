# pylint: disable=missing-function-docstring, missing-class-docstring, no-self-use, pointless-statement, protected-access, unused-argument, invalid-name
import pytest
from symaware.base import TimeIntervalAsyncLoopLock

from symaware.simulators.prescan import BoxEntity, Environment, Road, SphereEntity


class TestEnvironment:

    def test_environment_init(self):
        env = Environment()
        assert not env.entities
        assert not env.can_loop
        with pytest.raises(AttributeError):
            env.async_loop_lock

    def test_environment_init_async_loop(self):
        env = Environment(async_loop_lock=TimeIntervalAsyncLoopLock(1))
        assert not env.entities
        assert env.can_loop
        assert env.async_loop_lock is not None

    def test_environment_add_entity(self, environment: Environment, PatchedBoxEntity: type[BoxEntity]):
        entity = PatchedBoxEntity()
        environment.add_entities(entity)
        entity.initialise.assert_not_called()
        assert len(environment.entities) == 1
        assert environment.entities == {entity}

    def test_environment_add_entity_multiple(
        self, environment: Environment, PatchedBoxEntity: type[BoxEntity], PatchedSphereEntity: type[SphereEntity]
    ):
        entity1, entity2, entity3 = PatchedBoxEntity(), PatchedBoxEntity(), PatchedSphereEntity()
        environment.add_entities((entity1, entity2, entity3))
        entity1.initialise.call_count == 2
        entity3.initialise.assert_not_called()
        assert len(environment.entities) == 3
        assert environment.entities == {entity1, entity2, entity3}

    def test_environment_add_entity_idempotent(self, environment: Environment, PatchedBoxEntity: type[BoxEntity]):
        entity = PatchedBoxEntity()
        environment = Environment()
        environment.add_entities(entity)
        environment.add_entities(entity)
        entity.initialise.assert_not_called()
        assert len(environment.entities) == 1
        assert environment.entities == {entity}

    def test_environment_add_road(self):
        env = Environment()
        road = env.add_road()
        assert isinstance(road, Road)
