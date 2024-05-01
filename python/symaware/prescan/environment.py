from typing import TYPE_CHECKING

import numpy as np

from symaware.base.models import Entity, Environment
from symaware.base.utils import get_logger, log

from .entity import PrescanSpatialEntity
from ._symaware_prescan import _Environment, _Simulation

if TYPE_CHECKING:
    # String type hinting to support python 3.9
    from symaware.base.utils import AsyncLoopLock


class PrescanEnvironment(Environment):
    """
    Environment based on the prescan simulator.

    Args
    ----
    add_free_viewer:
        If True, a free camera will be added to the environment to allow for visualisation
    async_loop_lock:
        Async loop lock to use for the environment
    """

    __LOGGER = get_logger(__name__, "PrescanEnvironment")

    def __init__(
        self,
        add_free_viewer: bool = False,
        async_loop_lock: "AsyncLoopLock | None" = None,
    ):
        super().__init__(async_loop_lock)
        self._is_prescan_initialized = False
        self._internal_environment = _Environment()
        if add_free_viewer:
            self._internal_environment.create_free_viewer()
        self._internal_simulation = _Simulation(self._internal_environment)

    @log(__LOGGER)
    def get_entity_state(self, entity: Entity) -> np.ndarray:
        if not isinstance(entity, PrescanSpatialEntity):
            raise TypeError(f"Expected PrescanSpatialEntity, got {type(entity)}")
        return np.array(entity.state)

    @log(__LOGGER)
    def _add_entity(self, entity: Entity):
        if not isinstance(entity, PrescanSpatialEntity):
            raise TypeError(f"Expected PrescanSpatialEntity, got {type(entity)}")
        self._internal_environment.add_entity(entity._internal_entity)

    def step(self):
        self._internal_simulation.step()

    def stop(self):
        self._internal_simulation.terminate()
