from abc import abstractmethod
from dataclasses import dataclass, field

from symaware.base.models import (
    NullDynamicalModel,
    Entity as BaseEntity,
)

from ._symaware_prescan import (
    _Experiment,
    _WorldObject,
    _Entity,
    _Environment,
    Position,
    Orientation,
    SensorDetectability,
)
from .dynamical_model import DynamicalModel


@dataclass
class Entity(BaseEntity):
    """
    Abstract class for the entities using the Pescan simulator.
    Interacting with the Prescan simulator is delegated to the _internal_entity object, which is an instance of _Entity.
    A :class:`.PybulletDynamicalModel` can be associated with the entity in order to control its behaviour during the simulation.

    Note
    ----
    Do not manipulate the _internal_entity object directly.

    Args
    ----
    model:
        Dynamical model associated with the entity. Must be a subclass of :class:`.PybulletDynamicalModel`
    _internal_entity:
        Internal entity object used by the Prescan simulator's python bindings. Do not initialise this object directly.
    """

    model: DynamicalModel = field(default_factory=NullDynamicalModel)
    position = field(default_factory=Position)
    orientation = field(default_factory=Orientation)
    cog_offset = field(default_factory=Position)
    is_collision_detectable = True
    is_movable = True
    sensor_detectability: SensorDetectability = SensorDetectability.SensorDetectabilityDetectable
    _internal_entity: _Entity = None

    def __post_init__(self):
        super().__post_init__()
        if self._internal_entity is not None:
            raise ValueError("Do not initialise the _internal_entity object directly")
        self._internal_entity = _Entity(
            object_type=self.object_type,
            setup=_Entity.Setup(
                position=self.position,
                orientation=self.orientation,
                cog_offset=self.cog_offset,
                is_collision_detectable=self.is_collision_detectable,
                is_movable=self.is_movable,
                sensor_detectability=self.sensor_detectability,
            ),
            entity_model=(None if isinstance(self.model, NullDynamicalModel) else self.model.internal_model),
        )

    def apply_setup(self):
        """
        Update the internal entity object with the current setup of the entity.
        """
        self._internal_entity.apply_setup(
            _Entity.Setup(
                position=self.position,
                orientation=self.orientation,
                cog_offset=self.cog_offset,
                is_collision_detectable=self.is_collision_detectable,
                is_movable=self.is_movable,
                sensor_detectability=self.sensor_detectability,
            )
        )

    @property
    def name(self) -> str:
        """
        Unique name of the entity inside the Prescan experiment.

        Returns
        -------
            Name of the entity
        """
        return self._internal_entity.object.name

    @property
    def state(self) -> _Entity.State:
        """
        State of the entity inside the Prescan simulation.

        Returns
        -------
            State of the entity
        """
        return self._internal_entity.state

    @property
    @abstractmethod
    def object_type(self) -> _Environment.ObjectType:
        """
        Type of the entity in the Prescan environment.
        All the available types are defined in the _Environment.ObjectType enum.

        Returns
        -------
            Type of the entity
        """
        pass

    def initialise(self, experiment: _Experiment, object: _WorldObject):
        self._internal_entity.initialise_object(experiment, object)
        if not isinstance(self.model, NullDynamicalModel):
            self.model.initialise(experiment, object)


@dataclass
class AudiA3Entity(Entity):
    @property
    def object_type(self) -> _Environment.ObjectType:
        return _Environment.ObjectType.Audi_A3


@dataclass
class LexusGS450hFSportSedanEntity(Entity):
    @property
    def object_type(self) -> _Environment.ObjectType:
        return _Environment.ObjectType.Lexus_GS_450h_F_Sport_Sedan


@dataclass
class BalloonCarEntity(Entity):
    @property
    def object_type(self) -> _Environment.ObjectType:
        return _Environment.ObjectType.BalloonCar


@dataclass
class BoxEntity(Entity):
    @property
    def object_type(self) -> _Environment.ObjectType:
        return _Environment.ObjectType.Box


@dataclass
class SphereEntity(Entity):
    @property
    def object_type(self) -> _Environment.ObjectType:
        return _Environment.ObjectType.Sphere
