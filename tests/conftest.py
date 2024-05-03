# pylint: disable=missing-function-docstring, missing-class-docstring, redefined-outer-name, no-self-use, unused-argument, abstract-class-instantiated, invalid-name, protected-access
import os

import pytest
from pytest_mock import MockFixture
from symaware.base import AsyncLoopLock, DynamicalModel, Identifier

PRESCAN_DIR = "C:/Program Files/Simcenter Prescan/Prescan_2403"
os.add_dll_directory(f"{PRESCAN_DIR}/bin")
os.environ["PATH"] = f"{PRESCAN_DIR}/bin;{os.environ['PATH']}"

from symaware.simulators.prescan import (  # pylint: disable=wrong-import-position
    BoxEntity,
    Environment,
    SphereEntity,
)


class UniqueId:
    id: int = 0

    @classmethod
    def get(cls) -> int:
        cls.id += 1
        res = cls.id
        return res


@pytest.fixture(name="PatchedBoxEntity")
def fixture_PatchedBoxEntity(mocker: MockFixture) -> type[BoxEntity]:

    def fake_entity_initialise(self: BoxEntity):
        object.__setattr__(self, "id", UniqueId.get())

    mocker.patch.object(
        BoxEntity,
        "initialise",
        side_effect=fake_entity_initialise,
        autospec=True,
    )
    return BoxEntity


@pytest.fixture(name="PatchedSphereEntity")
def fixture_PatchedSphereEntity(mocker: MockFixture) -> type[SphereEntity]:

    def fake_entity_initialise(self: SphereEntity):
        object.__setattr__(self, "id", UniqueId.get())

    mocker.patch.object(
        SphereEntity,
        "initialise",
        side_effect=fake_entity_initialise,
        autospec=True,
    )
    return SphereEntity


@pytest.fixture(name="PatchedEnvironment")
def fixture_PatchedEnvironment(mocker: MockFixture) -> type[Environment]:

    def fake_env_initialise(self: Environment):
        self._is_pybullet_initialized = True

    def fake_entity_stop(self: Environment):
        self._is_pybullet_initialized = False

    mocker.patch.object(
        Environment,
        "initialise",
        autospec=True,
        side_effect=fake_env_initialise,
    )
    mocker.patch.object(
        Environment,
        "stop",
        autospec=True,
        side_effect=fake_entity_stop,
    )
    return Environment


class EnvironmentRequest(pytest.FixtureRequest):
    param: "AsyncLoopLock | tuple[AsyncLoopLock | None]"


@pytest.fixture(params=[0], name="environment")
def fixture_environment(request: EnvironmentRequest, PatchedEnvironment: type[Environment]) -> Environment:
    if isinstance(request.param, AsyncLoopLock):
        return PatchedEnvironment(request.param)
    if isinstance(request.param, tuple):
        return PatchedEnvironment(request.param[0])
    return PatchedEnvironment()


class BoxEntityRequest(pytest.FixtureRequest):
    param: "Identifier | DynamicalModel | tuple[DynamicalModel | None]"


@pytest.fixture(params=[0], name="box_entity")
def fixture_box_entity(request: BoxEntityRequest, PatchedBoxEntity: type[BoxEntity]) -> BoxEntity:
    if isinstance(request.param, Identifier):
        return PatchedBoxEntity(request.param)
    if isinstance(request.param, DynamicalModel):
        return PatchedBoxEntity(request.param.id, request.param)
    if isinstance(request.param, tuple):
        return PatchedBoxEntity(request.param[0].id, request.param[0])
    return PatchedBoxEntity()


class SphereEntityRequest(pytest.FixtureRequest):
    param: "Identifier | DynamicalModel | tuple[DynamicalModel | None]"


@pytest.fixture(params=[0], name="sphere_entity")
def fixture_sphere_entity(request: SphereEntityRequest, PatchedSphereEntity: type[SphereEntity]) -> SphereEntity:
    if isinstance(request.param, Identifier):
        return PatchedSphereEntity(request.param)
    if isinstance(request.param, DynamicalModel):
        return PatchedSphereEntity(request.param.id, request.param)
    if isinstance(request.param, tuple):
        return PatchedSphereEntity(request.param[0].id, request.param[0])
    return PatchedSphereEntity()
