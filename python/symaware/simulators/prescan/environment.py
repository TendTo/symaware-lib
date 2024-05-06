from typing import TYPE_CHECKING

import numpy as np
from symaware.base.models import Environment as BaseEnvironment
from symaware.base.models import NullDynamicalModel
from symaware.base.utils import get_logger, log

from ._symaware_prescan import Road, _Environment, _Simulation
from .entity import Entity, ExistingEntity

if TYPE_CHECKING:
    # String type hinting to support python 3.9
    from symaware.base.utils import AsyncLoopLock

    from ._symaware_prescan import Position
    from .dynamical_model import DynamicalModel


class Environment(BaseEnvironment):
    """
    Environment based on the prescan simulator.
    To use this environment, the correct version of the Prescan simulator must be installed on the machine.

    Example
    -------
    The following example shows how to create an environment with two agents and two entities.

    >>> form symaware.base import Agent, AgentCoordinator, TimeIntervalAsyncLoopLock
    >>> from symaware.simulators.prescan import (
    ...     BoxEntity,
    ...     Environment,
    ...     AmesimDynamicalModel,
    ...     )
    >>>
    >>> NUM_AGENTS = 2
    >>> TIME_INT = 0.5
    >>>
    >>> env = Environment(True, async_loop_lock=TimeIntervalAsyncLoopLock(TIME_INT))
    >>> env.add_entities((BoxEntity(position=np.array([2, 2, 2])), BoxEntity(position=np.array([2, -2, 1]))))
    >>>
    >>> agent_coordinator = AgentCoordinator[MyKnowledgeDatabase](env)
    >>> for i in range(NUM_AGENTS):
    ...     agent_entity = LexusGS450hFSportSedanEntity(
    ...         i, model=AmesimDynamicalModel(i), position=np.array([0, i, 0.1])
    ...     )
    ...     agent = Agent[MyKnowledgeDatabase](i, agent_entity)
    ...     env.add_agents(agent)
    ...     controller = MyController(agent.id, TimeIntervalAsyncLoopLock(TIME_INT))
    ...     risk = DefaultRiskEstimator(agent.id, TimeIntervalAsyncLoopLock(TIME_INT))
    ...     uncertainty = DefaultUncertaintyEstimator(agent.id, TimeIntervalAsyncLoopLock(TIME_INT))
    ...     perception = DefaultPerceptionSystem(agent.id, env, TimeIntervalAsyncLoopLock(TIME_INT))
    ...     communication = DefaultCommunicationSystem(
    ...         agent.id, TimeIntervalAsyncLoopLock(TIME_INT), TimeIntervalAsyncLoopLock(TIME_INT)
    ...     )
    ...     info_updater = DefaultInfoUpdater(agent.id)
    ...     agent.set_components(controller, risk, uncertainty, perception, communication, info_updater)
    ...     awareness_vector = AwarenessVector(agent.id, np.zeros(8))
    ...     knowledge_database = MyKnowledgeDatabase()
    ...     agent.initialise_agent(awareness_vector, {agent.id: knowledge_database})
    ...     agent_coordinator.add_agents(agent)
    >>>
    >>> agent_coordinator.async_run() # doctest: +SKIP


    Args
    ----
    filename:
        Name of the file that contains the experiment to load. Usually ends with .pb
        If not provided, a new empty environment will be created
    add_free_viewer:
        If True, a free camera will be added to the environment to allow for visualisation
    async_loop_lock:
        Async loop lock to use for the environment
    """

    __LOGGER = get_logger(__name__, "prescan.Environment")

    def __init__(
        self,
        filename: str = "",
        add_free_viewer: bool = False,
        async_loop_lock: "AsyncLoopLock | None" = None,
    ):
        super().__init__(async_loop_lock)
        self._is_prescan_initialized = False
        self._internal_environment = _Environment() if filename == "" else _Environment(filename)
        if add_free_viewer:
            self._internal_environment.create_free_viewer()
        self._internal_simulation = _Simulation(self._internal_environment)

    @log(__LOGGER)
    def get_entity_state(self, entity: Entity) -> np.ndarray:
        if not isinstance(entity, Entity):
            raise TypeError(f"Expected PrescanSpatialEntity, got {type(entity)}")
        return np.array(entity.state)

    @log(__LOGGER)
    def add_road(self, position: "Position | None" = None) -> Road:
        return (
            self._internal_environment.add_road(position)
            if position is not None
            else self._internal_environment.add_road()
        )

    @log(__LOGGER)
    def add_entity(self, entity_name: str, model: "DynamicalModel | None" = None) -> Entity:
        """
        Add an existing entity to the environment based on their name.
        The entity must exist within the internal experiment.
        If the entity was previously added to the environment, the entity object will be returned.
        Otherwise, the entity matching the name will be collected from the internal experiment and a new entity object
        will be created and returned.
        If a model is provided, the newly collected entity will be associated with the model.

        Args
        ----
        entity_name:
            Awareness database of the agent
        model:
            Knowledge database of the agent

        Returns
        -------
            Collected entity
        """
        entity = next((entity for entity in self._entities if entity.name == entity_name), None)
        if entity is not None:
            return entity

        internal_model = None if model is None else model._internal_model  # pylint: disable=protected-access
        internal_entity = self._internal_environment.add_entity(entity_name, internal_model)  # type: ignore
        entity = ExistingEntity(
            id=-1 if model is None else model.id,
            _internal_entity=internal_entity,
            model=NullDynamicalModel() if model is None else model,
        )
        return entity

    @log(__LOGGER)
    def _add_entity(self, entity: Entity):
        if not isinstance(entity, Entity):
            raise TypeError(f"Expected PrescanSpatialEntity, got {type(entity)}")
        self._internal_environment.add_entity(entity._internal_entity)  # pylint: disable=protected-access

    @log(__LOGGER)
    def initialise(self):
        if self._is_prescan_initialized:
            return
        self._internal_simulation.initialise()
        self._is_prescan_initialized = True

    def step(self):
        self._internal_simulation.step()

    @log(__LOGGER)
    def stop(self):
        if not self._is_prescan_initialized:
            return
        self._internal_simulation.terminate()
        self._is_prescan_initialized = False
