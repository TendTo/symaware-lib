from typing import TYPE_CHECKING

import numpy as np
from symaware.base.models import Environment as BaseEnvironment
from symaware.base.utils import get_logger, log

from ._symaware_prescan import (
    LogLevel,
    Road,
    SimulationSpeed,
    _Environment,
    _Simulation,
)
from .entity import Entity, ExistingEntity

if TYPE_CHECKING:
    # String type hinting to support python 3.9
    from typing import Callable, Iterable

    from symaware.base.utils import AsyncLoopLock

    from ._symaware_prescan import Position


class Environment(BaseEnvironment):
    """
    Environment based on the prescan simulator.
    To use this environment, the correct version of the Prescan simulator must be installed on the machine.

    Example
    -------
    The following example shows how to create an environment with two agents and two entities.

    >>> form symaware.base import Agent, AgentCoordinator, TimeIntervalAsyncLoopLock
    >>> from symaware.simulators.prescan import (
    ...         BoxEntity,
    ...         Environment,
    ...         AmesimDynamicalModel,
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
    async_loop_lock:
        Async loop lock to use for the environment
    """

    __LOGGER = get_logger(__name__, "prescan.Environment")

    def __init__(self, filename: str = "", async_loop_lock: "AsyncLoopLock | None" = None):
        super().__init__(async_loop_lock)
        self._is_prescan_initialized = False
        self._internal_environment = _Environment() if filename == "" else _Environment(filename)
        self._internal_simulation = _Simulation(self._internal_environment)

    @log(__LOGGER)
    def get_entity_state(self, entity: Entity) -> np.ndarray:
        """
        Get the state of the entity inside the simulation.
        Structured as follows:

        - position.x
        - position.y
        - position.z
        - orientation.roll
        - orientation.pitch
        - orientation.yaw
        - velocity
        - yaw_rate

        Args
        ----
        Entity to get the state from

        Returns
        -------
        State of the entity
        """
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

    def set_log_level(self, log_level: LogLevel):
        """
        Set the log level of the Prescan simulator

        Args
        ----
        log_level:
            log level the Prescan simulator will use
        """
        self._internal_simulation.set_log_level(log_level)

    def _set_on_pre_step(self, callback: "Callable[[], None] | None"):
        """
        Set a callback to be called as the first operation at each simulation step.
        If none, the callback will be removed.

        Note
        ----
        The callback will be removed when the environment is stopped.

        Args
        ----
        callback:
            callback to be called as the first operation at each simulation step
            If None, the callback will be removed
        """
        if callback is None:
            self._internal_simulation.remove_on_pre_step()
        else:
            self._internal_simulation.set_on_pre_step(callback)

    def _set_on_post_step(self, callback: "Callable[[], None] | None"):
        """
        Set a callback to be called as the last operation at each simulation step.
        If None, the callback will be removed.

        Note
        ----
        The callback will be removed when the environment is stopped.

        Args
        ----
        callback:
            callback to be called as the last operation at each simulation step.
            If None, the callback will be removed
        """
        if callback is None:
            self._internal_simulation.remove_on_post_step()
        else:
            self._internal_simulation.set_on_post_step(callback)

    def _notify_stepping(self):
        """Run the `_notify` method for the `stepping` event"""
        self._notify("stepping", self)

    def _notify_stepped(self):
        """Run the `_notify` method for the `stepping` event"""
        self._notify("stepped", self)

    def set_scheduler_frequencies(self, simulation_frequency: int, integration_frequency: int):
        """
        Set the frequency of the scheduler

        Args
        ----
        simulation_frequency:
            frequency of the simulation
        integration_frequency:
            frequency of the intgration
        """
        self._internal_environment.set_scheduler_frequencies(simulation_frequency, integration_frequency)

    def set_scheduler_speed(self, simulation_speed: SimulationSpeed, ignore_frame_overrun: bool):
        """
        Set the speed of the scheduler

        Args
        ----
        simulation_speed:
            speed of the simulation
        ignore_frame_overrun:
            whether to ignore frames that take to long to run
        """
        self._internal_environment.set_scheduler_speed(simulation_speed, ignore_frame_overrun)

    def import_open_drive_network(self, filename: str):
        """
        Load the OpenDrive network from a file

        Args
        ----
        filename:
            path to the file containing the OpenDrive network
        """
        self._internal_environment.import_open_drive_network(filename)

    def add_free_viewer(self):
        """
        Add a free camera to the environment, to ease visualization
        """
        self._internal_environment.add_free_viewer()

    @log(__LOGGER)
    def add_entity(self, entity_name: str, entity: "Entity"):
        """
        Add an existing entity to the environment based on their name.
        The entity must already exist within the internal experiment.

        Args
        ----
        entity_name:
            Name of the entity in the experimenet
        entity:
            Pre-existing entity to add
        """
        if not isinstance(entity, Entity):
            raise TypeError(f"Expected PrescanSpatialEntity, got {type(entity)}")
        self._internal_environment.add_entity(entity_name, entity._internal_entity)  # pylint: disable=protected-access

    def remove_entities(self, entities: "Entity | str | Iterable[Entity | str]"):
        """
        Remove all the entities from the environment, based on the type of the entity parameter:
        - **string**: it will be removed by the experiment name.
        - **ExistingEntity**: it will be removed by the experiment by name and from the environment.
        - **Entity**: it will be removed by environment and experiment using the internal entity.

        Args
        ----
        entity:
            Entities to remove
        """
        if isinstance(entities, str):
            entities = (entities,)
        elif isinstance(entities, Entity):
            entities = (entities,)
        for entity in entities:
            if isinstance(entity, str):
                self._internal_environment.remove_entity(entity)
                continue
            if isinstance(entity, ExistingEntity):
                self.entities.discard(entity)
                self._internal_environment.remove_entity(entity.object_name)
                continue
            if not isinstance(entities, Entity):
                self.__LOGGER.error(f"Expected PrescanSpatialEntity, got {type(entities)}")
                continue
            self.entities.discard(entities)
            self._internal_environment.remove_entity(entities._internal_entity)  # pylint: disable=protected-access

    @log(__LOGGER)
    def _add_entity(self, entity: Entity):
        if not isinstance(entity, Entity):
            raise TypeError(f"Expected PrescanSpatialEntity, got {type(entity)}")
        if isinstance(entity, ExistingEntity):
            self.add_entity(entity.object_name, entity)
            return
        self._internal_environment.add_entity(entity._internal_entity)  # pylint: disable=protected-access

    @log(__LOGGER)
    def initialise(self):
        if self._is_prescan_initialized:
            return
        self._notify("initialising", self)
        self._internal_simulation.initialise()
        self._set_on_pre_step(self._notify_stepping)
        self._set_on_post_step(self._notify_stepped)
        self._is_prescan_initialized = True
        self._notify("initialised", self)

    def step(self):
        self._internal_simulation.step()

    @log(__LOGGER)
    def stop(self):
        if not self._is_prescan_initialized:
            return
        self._set_on_pre_step(None)
        self._set_on_post_step(None)
        self._internal_simulation.terminate()
        self._is_prescan_initialized = False
