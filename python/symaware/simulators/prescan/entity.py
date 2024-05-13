from abc import abstractmethod
from dataclasses import dataclass, field

import numpy as np
from symaware.base import Entity as BaseEntity
from symaware.base import Identifier, NullDynamicalModel

from ._symaware_prescan import (
    ObjectType,
    Orientation,
    Position,
    SensorDetectability,
    _Entity,
    _Experiment,
    _WorldObject,
)
from .dynamical_model import DynamicalModel
from .sensor import Sensor


@dataclass(frozen=True, init=False)
class Entity(BaseEntity):
    """
    Abstract class for the entities using the Pescan simulator.
    Interacting with the Prescan simulator is delegated to the _internal_entity object, which is an instance of _Entity.
    A :class:`.PybulletDynamicalModel` can be associated with the entity
    in order to control its behaviour during the simulation.

    Note
    ----
    Do not manipulate the _internal_entity object directly.

    Args
    ----
    model:
        Dynamical model associated with the entity. Must be a subclass of :class:`.PybulletDynamicalModel`
    """

    model: DynamicalModel = field(default_factory=NullDynamicalModel)
    sensors: tuple[Sensor] = field(default_factory=tuple)
    _internal_entity: _Entity = None  # type: ignore

    def __init__(
        self,
        id: Identifier = -1,  # pylint: disable=redefined-builtin
        model: DynamicalModel = NullDynamicalModel(),
        position: "Position | np.ndarray" = Position(),
        orientation: "Orientation | np.ndarray" = Orientation(),
        cog_offset: "Position | np.ndarray" = Position(),
        is_collision_detectable: bool = True,
        is_movable: bool = True,
        sensor_detectability: SensorDetectability = SensorDetectability.SensorDetectabilityDetectable,
        sensors: "tuple[Sensor] | Sensor" = tuple(),
    ):
        object.__setattr__(self, "id", id)
        object.__setattr__(self, "model", model)
        object.__setattr__(self, "sensors", sensors if isinstance(sensors, tuple) else (sensors,))
        setup = _Entity.Setup(
            position=Position(position) if isinstance(position, np.ndarray) else position,
            orientation=Orientation(orientation) if isinstance(orientation, np.ndarray) else orientation,
            cog_offset=Position(cog_offset) if isinstance(cog_offset, np.ndarray) else cog_offset,
            is_collision_detectable=is_collision_detectable,
            is_movable=is_movable,
            sensor_detectability=sensor_detectability,
        )
        entity_model = None if isinstance(model, NullDynamicalModel) else model.internal_model
        object.__setattr__(
            self, "_internal_entity", _Entity(object_type=self.object_type, setup=setup, entity_model=entity_model)
        )

        assert isinstance(self.sensors, tuple), "sensors must be a tuple of sensors"
        for sensor in self.sensors:
            self._internal_entity.add_sensor(sensor._internal_sensor)  # pylint: disable=protected-access

    def apply_setup(
        self,
        position: "Position | np.ndarray" = Position(),
        orientation: "Orientation | np.ndarray" = Orientation(),
        cog_offset: "Position | np.ndarray" = Position(),
        is_collision_detectable: bool = True,
        is_movable: bool = True,
        sensor_detectability: SensorDetectability = SensorDetectability.SensorDetectabilityDetectable,
    ):
        """
        Update the internal entity object with the current setup of the entity.
        """
        self._internal_entity.apply_setup(
            _Entity.Setup(
                position=Position(position) if isinstance(position, np.ndarray) else position,
                orientation=Orientation(orientation) if isinstance(orientation, np.ndarray) else orientation,
                cog_offset=Position(cog_offset) if isinstance(cog_offset, np.ndarray) else cog_offset,
                is_collision_detectable=is_collision_detectable,
                is_movable=is_movable,
                sensor_detectability=sensor_detectability,
            )
        )

    def get_sensor_of_type(self, sensor_type: type[Sensor]) -> Sensor:
        """
        Get the sensor of the specified type.

        Args
        ----
        sensor_type:
            Type of the sensor to retrieve

        Returns
        -------
            Sensor of the specified type

        Raises
        -----
            IndexError: If no sensor of the specified type is found
        """
        for sensor in self.sensors:
            if isinstance(sensor, sensor_type):
                return sensor
        raise IndexError(f"No sensor of type {sensor_type} found")

    def get_sensors_of_type(self, sensor_type: type[Sensor]) -> list[Sensor]:
        """
        Get a list of sensors of the specified type.

        Args
        ----
        sensor_type:
            Type of the sensors to retrieve

        Returns
        -------
            Sensors of the specified type
        """
        sensors = []
        for sensor in self.sensors:
            if isinstance(sensor, sensor_type):
                sensors.append(sensor)
        return sensors

    @property
    def name(self) -> str:
        """Unique name of the entity inside the Prescan experiment"""
        return self._internal_entity.object.name

    @property
    def state(self) -> _Entity.State:
        """State of the entity inside the Prescan simulation"""
        return self._internal_entity.state

    @property
    def is_initialised(self) -> bool:
        """Whether the entity has already been initialised inside the environment"""
        return self._internal_entity.is_initialised

    @property
    def cog_offset(self) -> Position:
        """Center of gravity offset"""
        if self.is_initialised:
            return self._internal_entity.object.cog_offset
        return self._internal_entity.setup.cog_offset

    @property
    def is_collision_detectable(self) -> bool:
        """Whether the entity is collision detectable"""
        if self.is_initialised:
            return self._internal_entity.object.collision_detectable
        return self._internal_entity.setup.is_collision_detectable

    @property
    def position(self) -> Position:
        """Position of the entity in the setup"""
        if self.is_initialised:
            return self._internal_entity.object.position
        return self._internal_entity.setup.position

    @property
    def orientation(self) -> Orientation:
        """Orientation of the entity"""
        if self.is_initialised:
            return self._internal_entity.object.orientation
        return self._internal_entity.setup.orientation

    @property
    def is_movable(self) -> bool:
        """Whether the entity is movable"""
        if self.is_initialised:
            return self._internal_entity.object.movable
        return self._internal_entity.setup.is_movable

    @property
    def sensor_detectability(self) -> SensorDetectability:
        """What kind of sensors are able to detect this entity"""
        if self.is_initialised:
            return self._internal_entity.object.sensor_detectability
        return self._internal_entity.setup.sensor_detectability

    @property
    @abstractmethod
    def object_type(self) -> ObjectType:
        """
        Type of the entity in the Prescan environment.
        All the available types are defined in the ObjectType enum.

        Returns
        -------
            Type of the entity
        """
        pass

    def initialise(self, experiment: _Experiment, obj: _WorldObject):
        self._internal_entity.initialise_object(experiment, obj)
        if not isinstance(self.model, NullDynamicalModel):
            self.model.initialise(experiment, obj)  # pylint: disable=too-many-function-args


@dataclass(frozen=True, init=False)
class ADACtargetyellowmercEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ADAC_target_yellow_merc


@dataclass(frozen=True, init=False)
class ApartmentBuildingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ApartmentBuilding


@dataclass(frozen=True, init=False)
class ArrowBoardTrailerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ArrowBoard_Trailer


@dataclass(frozen=True, init=False)
class Ash10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Ash10y


@dataclass(frozen=True, init=False)
class Ash20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Ash20y


@dataclass(frozen=True, init=False)
class AudiA3Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Audi_A3


@dataclass(frozen=True, init=False)
class AudiA8SedanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Audi_A8_Sedan


@dataclass(frozen=True, init=False)
class AustrianPine10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.AustrianPine10y


@dataclass(frozen=True, init=False)
class AustrianPine20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.AustrianPine20y


@dataclass(frozen=True, init=False)
class BEPoliceVolvoXC60Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BE_Police_Volvo_XC60


@dataclass(frozen=True, init=False)
class BMWX5SUVEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BMW_X5_SUV


@dataclass(frozen=True, init=False)
class BMWZ3ConvertibleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BMW_Z3_Convertible


@dataclass(frozen=True, init=False)
class BalloonCarEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BalloonCar


@dataclass(frozen=True, init=False)
class BarrierFenceEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BarrierFence


@dataclass(frozen=True, init=False)
class Birch10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Birch10y


@dataclass(frozen=True, init=False)
class Birch20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Birch20y


@dataclass(frozen=True, init=False)
class BlueSpruce10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BlueSpruce10y


@dataclass(frozen=True, init=False)
class BlueSpruce20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BlueSpruce20y


@dataclass(frozen=True, init=False)
class BottsDotsWhiteEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BottsDots_White


@dataclass(frozen=True, init=False)
class BottsDotsYellowEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BottsDots_Yellow


@dataclass(frozen=True, init=False)
class Boy100Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Boy_100


@dataclass(frozen=True, init=False)
class Boy150Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Boy_150


@dataclass(frozen=True, init=False)
class Building00AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_00A


@dataclass(frozen=True, init=False)
class Building01AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_01A


@dataclass(frozen=True, init=False)
class Building02AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_02A


@dataclass(frozen=True, init=False)
class Building03AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_03A


@dataclass(frozen=True, init=False)
class Building04AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_04A


@dataclass(frozen=True, init=False)
class Building05AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_05A


@dataclass(frozen=True, init=False)
class Building06AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_06A


@dataclass(frozen=True, init=False)
class Building07AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_07A


@dataclass(frozen=True, init=False)
class Building08AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_08A


@dataclass(frozen=True, init=False)
class BusstopEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Busstop


@dataclass(frozen=True, init=False)
class CAT725Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CAT_725


@dataclass(frozen=True, init=False)
class CadillacEscaladeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cadillac_Escalade


@dataclass(frozen=True, init=False)
class CarDealerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CarDealer


@dataclass(frozen=True, init=False)
class CarTrailerSmallEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Car_Trailer_Small


@dataclass(frozen=True, init=False)
class CatsEyesREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesR


@dataclass(frozen=True, init=False)
class CatsEyesWEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesW


@dataclass(frozen=True, init=False)
class CatsEyesWREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesWR


@dataclass(frozen=True, init=False)
class CatsEyesWYEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesWY


@dataclass(frozen=True, init=False)
class CatsEyesYEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesY


@dataclass(frozen=True, init=False)
class ChildLeaningEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Child_Leaning


@dataclass(frozen=True, init=False)
class ChildOverweightEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Child_Overweight


@dataclass(frozen=True, init=False)
class ChildRegularEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Child_Regular


@dataclass(frozen=True, init=False)
class ChildSittingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Child_Sitting


@dataclass(frozen=True, init=False)
class CinderBlockAEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CinderBlock_A


@dataclass(frozen=True, init=False)
class CinderBlockBEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CinderBlock_B


@dataclass(frozen=True, init=False)
class CinderBlockCEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CinderBlock_C


@dataclass(frozen=True, init=False)
class CitroenC3HatchbackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Citroen_C3_Hatchback


@dataclass(frozen=True, init=False)
class ConstructionSignJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ConstructionSign_JP


@dataclass(frozen=True, init=False)
class ContainerTrailerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Container_Trailer


@dataclass(frozen=True, init=False)
class CornerReflector138mmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CornerReflector138mm


@dataclass(frozen=True, init=False)
class CornerReflector1768mmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CornerReflector176_8mm


@dataclass(frozen=True, init=False)
class CornerReflector4635mmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CornerReflector46_35mm


@dataclass(frozen=True, init=False)
class CottonAEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cotton_A


@dataclass(frozen=True, init=False)
class CottonBEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cotton_B


@dataclass(frozen=True, init=False)
class CottonCEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cotton_C


@dataclass(frozen=True, init=False)
class DAF95XFEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.DAF_95_XF


@dataclass(frozen=True, init=False)
class DAFEuro6XFEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.DAF_Euro_6_XF


@dataclass(frozen=True, init=False)
class DeerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Deer


@dataclass(frozen=True, init=False)
class Dogwood10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Dogwood10y


@dataclass(frozen=True, init=False)
class Dogwood20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Dogwood20y


@dataclass(frozen=True, init=False)
class Dumpster2300LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Dumpster_2300L


@dataclass(frozen=True, init=False)
class DutchChurchEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.DutchChurch


@dataclass(frozen=True, init=False)
class EmptyLightNodeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Empty_Light_Node


@dataclass(frozen=True, init=False)
class ExistingEntity(Entity):
    """
    Existing entity.
    Used to load an entity from an experiment file without having to recreate it.
    The object_name will be used to link the entity to the corresponding World object in the experiment file.
    """

    object_name: str = ""

    def __init__(
        self,
        id: Identifier = -1,  # pylint: disable=redefined-builtin
        model: DynamicalModel = NullDynamicalModel(),
        object_name: str = "",
        position: "Position | np.ndarray" = Position(),
        orientation: "Orientation | np.ndarray" = Orientation(),
        cog_offset: "Position | np.ndarray" = Position(),
        is_collision_detectable: bool = True,
        is_movable: bool = True,
        sensor_detectability: SensorDetectability = SensorDetectability.SensorDetectabilityDetectable,
        sensors: "tuple[Sensor] | Sensor" = tuple(),
    ):
        super().__init__(
            id=id,
            model=model,
            position=position,
            orientation=orientation,
            cog_offset=cog_offset,
            is_collision_detectable=is_collision_detectable,
            is_movable=is_movable,
            sensor_detectability=sensor_detectability,
            sensors=sensors,
        )
        if object_name == "":
            raise AttributeError(
                "object_name must contain the unique name of the WorldObject in the Prescan experiment"
            )
        object.__setattr__(self, "object_name", object_name)

    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Existing


@dataclass(frozen=True, init=False)
class FAWJiefangJ6MEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FAW_Jiefang_J6M


@dataclass(frozen=True, init=False)
class FShape150cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FShape150cm


@dataclass(frozen=True, init=False)
class FShape250cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FShape250cm


@dataclass(frozen=True, init=False)
class FShape350cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FShape350cm


@dataclass(frozen=True, init=False)
class FemaleBendingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_Bending


@dataclass(frozen=True, init=False)
class FemaleLeaningEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_Leaning


@dataclass(frozen=True, init=False)
class FemaleOverweightEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_Overweight


@dataclass(frozen=True, init=False)
class FemaleRegularEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_Regular


@dataclass(frozen=True, init=False)
class FemalewBuggyEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_wBuggy


@dataclass(frozen=True, init=False)
class FemalewLongCoatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_wLongCoat


@dataclass(frozen=True, init=False)
class FemalewRaincoatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_wRaincoat


@dataclass(frozen=True, init=False)
class FemalewShoppingCartEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_wShoppingCart


@dataclass(frozen=True, init=False)
class FiatBravoHatchbackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Fiat_Bravo_Hatchback


@dataclass(frozen=True, init=False)
class FireBrigadeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FireBrigade


@dataclass(frozen=True, init=False)
class FordFiestaHatchbackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Ford_Fiesta_Hatchback


@dataclass(frozen=True, init=False)
class FordFocusStationwagonEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Ford_Focus_Stationwagon


@dataclass(frozen=True, init=False)
class FullTrailerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Full_Trailer


@dataclass(frozen=True, init=False)
class GarageGroundFloorEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Garage_Ground_Floor


@dataclass(frozen=True, init=False)
class GarageMidFloorEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Garage_Mid_Floor


@dataclass(frozen=True, init=False)
class GarageTopFloorEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Garage_Top_Floor


@dataclass(frozen=True, init=False)
class GasStationEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GasStation


@dataclass(frozen=True, init=False)
class GenesisGV80Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Genesis_GV80


@dataclass(frozen=True, init=False)
class GuardrailReflectorRectREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RectR


@dataclass(frozen=True, init=False)
class GuardrailReflectorRectWEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RectW


@dataclass(frozen=True, init=False)
class GuardrailReflectorRectWREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RectWR


@dataclass(frozen=True, init=False)
class GuardrailReflectorRoundREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RoundR


@dataclass(frozen=True, init=False)
class GuardrailReflectorRoundWEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RoundW


@dataclass(frozen=True, init=False)
class GuardrailReflectorRoundWREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RoundWR


@dataclass(frozen=True, init=False)
class GuardrailReflectorRoundYEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RoundY


@dataclass(frozen=True, init=False)
class GuidedSoftTargetEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuidedSoftTarget


@dataclass(frozen=True, init=False)
class HOWOT5GCementTruckEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HOWO_T5G_Cement_Truck


@dataclass(frozen=True, init=False)
class HinoBlueRibbonEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Hino_Blue_Ribbon


@dataclass(frozen=True, init=False)
class HondaPanEuropeanMotorcycleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Honda_Pan_European_Motorcycle


@dataclass(frozen=True, init=False)
class HondaPanEuropeanMotorcycleWithDriverEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Honda_Pan_European_Motorcycle_With_Driver


@dataclass(frozen=True, init=False)
class HouseModernEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseModern


@dataclass(frozen=True, init=False)
class HouseOld1Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld1


@dataclass(frozen=True, init=False)
class HouseOld2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld2


@dataclass(frozen=True, init=False)
class HouseOld3Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld3


@dataclass(frozen=True, init=False)
class HouseOld4Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld4


@dataclass(frozen=True, init=False)
class HouseOld5Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld5


@dataclass(frozen=True, init=False)
class HouseOld6Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld6


@dataclass(frozen=True, init=False)
class Houses1930sEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Houses1930s


@dataclass(frozen=True, init=False)
class HyundaiIoniq5Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Hyundai_Ioniq5


@dataclass(frozen=True, init=False)
class Hyundaii30NLineEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Hyundai_i30_NLine


@dataclass(frozen=True, init=False)
class IsuzuDMaxEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Isuzu_DMax


@dataclass(frozen=True, init=False)
class IsuzuGigaFireTruckEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Isuzu_Giga_Fire_Truck


@dataclass(frozen=True, init=False)
class JACHFCSeriesEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.JAC_HFC_Series


@dataclass(frozen=True, init=False)
class JapaneseMaple10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.JapaneseMaple10y


@dataclass(frozen=True, init=False)
class JapaneseMaple20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.JapaneseMaple20y


@dataclass(frozen=True, init=False)
class JobyAviationS4Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Joby_Aviation_S4


@dataclass(frozen=True, init=False)
class KiaEV6Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Kia_EV6


@dataclass(frozen=True, init=False)
class KiaEV6wRoofRackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Kia_EV6_wRoofRack


@dataclass(frozen=True, init=False)
class KiaEV6wRoofRackSiemensEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Kia_EV6_wRoofRack_Siemens


@dataclass(frozen=True, init=False)
class LexusGS450hFSportSedanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Lexus_GS_450h_F_Sport_Sedan


@dataclass(frozen=True, init=False)
class LexusLS600hFSportEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Lexus_LS_600h_F_Sport


@dataclass(frozen=True, init=False)
class LightPostEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.LightPost


@dataclass(frozen=True, init=False)
class Lilac10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Lilac10y


@dataclass(frozen=True, init=False)
class Lilac20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Lilac20y


@dataclass(frozen=True, init=False)
class Magnolia10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Magnolia10y


@dataclass(frozen=True, init=False)
class Magnolia20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Magnolia20y


@dataclass(frozen=True, init=False)
class Male200Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_200


@dataclass(frozen=True, init=False)
class MaleAfricanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_African


@dataclass(frozen=True, init=False)
class MaleBendingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Bending


@dataclass(frozen=True, init=False)
class MaleBendingOverEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_BendingOver


@dataclass(frozen=True, init=False)
class MaleCyclingCyclistEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_CyclingCyclist


@dataclass(frozen=True, init=False)
class MaleFemaleHandInHandEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Female_HandInHand


@dataclass(frozen=True, init=False)
class MaleLargeShoulderSuitcaseEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_LargeShoulderSuitcase


@dataclass(frozen=True, init=False)
class MaleLeaningEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Leaning


@dataclass(frozen=True, init=False)
class MaleLeaningBackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_LeaningBack


@dataclass(frozen=True, init=False)
class MaleLyingDownEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_LyingDown


@dataclass(frozen=True, init=False)
class MaleOldWhiteWithStickEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Old_White_WithStick


@dataclass(frozen=True, init=False)
class MaleOldWhiteWithWalkerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Old_White_WithWalker


@dataclass(frozen=True, init=False)
class MaleOldWhiteWithWalkerWithWheelsEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Old_White_WithWalkerWithWheels


@dataclass(frozen=True, init=False)
class MaleOverweightEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Overweight


@dataclass(frozen=True, init=False)
class MaleRegularEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Regular


@dataclass(frozen=True, init=False)
class MaleShoppingBagEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_ShoppingBag


@dataclass(frozen=True, init=False)
class MaleSittingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Sitting


@dataclass(frozen=True, init=False)
class MalewBackpackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wBackpack


@dataclass(frozen=True, init=False)
class MalewBicycleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wBicycle


@dataclass(frozen=True, init=False)
class MalewLargeBackpackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wLargeBackpack


@dataclass(frozen=True, init=False)
class MalewLongCoatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wLongCoat


@dataclass(frozen=True, init=False)
class MalewRaincoatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wRaincoat


@dataclass(frozen=True, init=False)
class MalewSuitEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wSuit


@dataclass(frozen=True, init=False)
class MalewSuitcaseEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wSuitcase


@dataclass(frozen=True, init=False)
class Man250Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Man_250


@dataclass(frozen=True, init=False)
class ManAsianEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Man_Asian


@dataclass(frozen=True, init=False)
class MazdaRX8CoupeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Mazda_RX8_Coupe


@dataclass(frozen=True, init=False)
class MercedesBenzActros1851LS4x2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.MercedesBenz_Actros_1851_LS_4x2


@dataclass(frozen=True, init=False)
class MercedesBenzActros1860LS4x2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.MercedesBenz_Actros_1860_LS_4x2


@dataclass(frozen=True, init=False)
class MercedesBenzActros2541L6x2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.MercedesBenz_Actros_2541_L_6x2


@dataclass(frozen=True, init=False)
class MitsubishiOutlanderPHEVEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Mitsubishi_Outlander_PHEV


@dataclass(frozen=True, init=False)
class MonumentEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Monument


@dataclass(frozen=True, init=False)
class NCAPAdultEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Adult


@dataclass(frozen=True, init=False)
class NCAPChildEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Child


@dataclass(frozen=True, init=False)
class NCAPCyclistEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Cyclist


@dataclass(frozen=True, init=False)
class NCAPEBTAEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_EBTA


@dataclass(frozen=True, init=False)
class NCAPGVTEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_GVT


@dataclass(frozen=True, init=False)
class NCAPMotorcycleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Motorcycle


@dataclass(frozen=True, init=False)
class NCAPScooterEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Scooter


@dataclass(frozen=True, init=False)
class NCAPStreetLightEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_StreetLight


@dataclass(frozen=True, init=False)
class NLAmbulanceVolvoXC60Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NL_Ambulance_Volvo_XC60


@dataclass(frozen=True, init=False)
class NissanAriyaEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Nissan_Ariya


@dataclass(frozen=True, init=False)
class NissanCabstarBoxtruckEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Nissan_Cabstar_Boxtruck


@dataclass(frozen=True, init=False)
class OfficeBrownFlatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OfficeBrownFlat


@dataclass(frozen=True, init=False)
class OfficeBrownTall1Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OfficeBrownTall1


@dataclass(frozen=True, init=False)
class OfficeBrownTall2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OfficeBrownTall2


@dataclass(frozen=True, init=False)
class OfficeGreenTallEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OfficeGreenTall


@dataclass(frozen=True, init=False)
class Overhang1LightJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Light_JP


@dataclass(frozen=True, init=False)
class Overhang1LightKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Light_KR


@dataclass(frozen=True, init=False)
class Overhang1LightNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Light_NL


@dataclass(frozen=True, init=False)
class Overhang1LightUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Light_US


@dataclass(frozen=True, init=False)
class Overhang1PostJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Post_JP


@dataclass(frozen=True, init=False)
class Overhang1PostKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Post_KR


@dataclass(frozen=True, init=False)
class Overhang1PostNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Post_NL


@dataclass(frozen=True, init=False)
class Overhang1PostUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Post_US


@dataclass(frozen=True, init=False)
class Overhang2LightsJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Lights_JP


@dataclass(frozen=True, init=False)
class Overhang2LightsKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Lights_KR


@dataclass(frozen=True, init=False)
class Overhang2LightsNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Lights_NL


@dataclass(frozen=True, init=False)
class Overhang2LightsUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Lights_US


@dataclass(frozen=True, init=False)
class Overhang2PostJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Post_JP


@dataclass(frozen=True, init=False)
class Overhang2PostKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Post_KR


@dataclass(frozen=True, init=False)
class Overhang2PostNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Post_NL


@dataclass(frozen=True, init=False)
class Overhang2PostUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Post_US


@dataclass(frozen=True, init=False)
class OverhangDH2LightsUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OverhangDH2Lights_US


@dataclass(frozen=True, init=False)
class OverhangDHPostUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OverhangDHPost_US


@dataclass(frozen=True, init=False)
class PalletEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Pallet


@dataclass(frozen=True, init=False)
class PedestrianSignalJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PedestrianSignal_JP


@dataclass(frozen=True, init=False)
class Peterbilt579Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Peterbilt_579


@dataclass(frozen=True, init=False)
class Peterbilt579TrailerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Peterbilt_579_Trailer


@dataclass(frozen=True, init=False)
class PlasticBarrier100cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PlasticBarrier100cm


@dataclass(frozen=True, init=False)
class PrismSignV305070Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSignV_30_50_70


@dataclass(frozen=True, init=False)
class PrismSignV51015Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSignV_5_10_15


@dataclass(frozen=True, init=False)
class PrismSignV80100110Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSignV_80_100_110


@dataclass(frozen=True, init=False)
class PrismSign305070Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSign_30_50_70


@dataclass(frozen=True, init=False)
class PrismSign51015Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSign_5_10_15


@dataclass(frozen=True, init=False)
class PrismSign80100110Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSign_80_100_110


@dataclass(frozen=True, init=False)
class Pylon01Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Pylon_01


@dataclass(frozen=True, init=False)
class Pylon02Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Pylon_02


@dataclass(frozen=True, init=False)
class ReflectorSignEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ReflectorSign


@dataclass(frozen=True, init=False)
class ReflectorSignSimpleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ReflectorSignSimple


@dataclass(frozen=True, init=False)
class RivianR1TEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Rivian_R1T


@dataclass(frozen=True, init=False)
class RivianR1TwCoverEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Rivian_R1T_wCover


@dataclass(frozen=True, init=False)
class RoadClosedwLightsEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadClosed_wLights


@dataclass(frozen=True, init=False)
class RoadsideLightNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadsideLight_NL


@dataclass(frozen=True, init=False)
class RoadsideMarkerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadsideMarker


@dataclass(frozen=True, init=False)
class RoadsidePostEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadsidePost


@dataclass(frozen=True, init=False)
class RoadsidePostNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadsidePost_NL


@dataclass(frozen=True, init=False)
class Roewe550SSedanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Roewe_550_S_Sedan


@dataclass(frozen=True, init=False)
class RowCropTractorEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Row_Crop_Tractor


@dataclass(frozen=True, init=False)
class SchoolEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.School


@dataclass(frozen=True, init=False)
class ScooterEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Scooter


@dataclass(frozen=True, init=False)
class ScooterwBoxEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Scooter_wBox


@dataclass(frozen=True, init=False)
class Serviceberry10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Serviceberry10y


@dataclass(frozen=True, init=False)
class Serviceberry15yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Serviceberry15y


@dataclass(frozen=True, init=False)
class Serviceberry5yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Serviceberry5y


@dataclass(frozen=True, init=False)
class ShoppingCartEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ShoppingCart


@dataclass(frozen=True, init=False)
class SiemenseRodEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Siemens_eRod


@dataclass(frozen=True, init=False)
class SignalCasing20cmNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing20cm_NL


@dataclass(frozen=True, init=False)
class SignalCasing30cmDHUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing30cmDH_US


@dataclass(frozen=True, init=False)
class SignalCasing30cmJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing30cm_JP


@dataclass(frozen=True, init=False)
class SignalCasing30cmNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing30cm_NL


@dataclass(frozen=True, init=False)
class SignalCasing30cmUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing30cm_US


@dataclass(frozen=True, init=False)
class SignalCasing330cmKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing3_30cm_KR


@dataclass(frozen=True, init=False)
class SignalCasing430cmKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing4_30cm_KR


@dataclass(frozen=True, init=False)
class SkywellEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Skywell


@dataclass(frozen=True, init=False)
class SpeedBump250cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpeedBump250cm


@dataclass(frozen=True, init=False)
class SpeedBump350cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpeedBump350cm


@dataclass(frozen=True, init=False)
class SportsBikeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Sports_Bike


@dataclass(frozen=True, init=False)
class SportsBikewDriverEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Sports_Bike_wDriver


@dataclass(frozen=True, init=False)
class SpringPost46cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpringPost46cm


@dataclass(frozen=True, init=False)
class SpringPost75cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpringPost75cm


@dataclass(frozen=True, init=False)
class SpringPost95cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpringPost95cm


@dataclass(frozen=True, init=False)
class SuzukiHustlerHybridEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Suzuki_Hustler_Hybrid


@dataclass(frozen=True, init=False)
class TerracedHousesEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TerracedHouses


@dataclass(frozen=True, init=False)
class TeslaModel3Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Tesla_Model_3


@dataclass(frozen=True, init=False)
class TireHorizontalEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Tire_Horizontal


@dataclass(frozen=True, init=False)
class TireVerticalEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Tire_Vertical


@dataclass(frozen=True, init=False)
class Toddler050Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Toddler_050


@dataclass(frozen=True, init=False)
class ToyotaPreviaMPVEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Toyota_Previa_MPV


@dataclass(frozen=True, init=False)
class ToyotaPriusSedanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Toyota_Prius_Sedan


@dataclass(frozen=True, init=False)
class ToyotaYarisHatchbackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Toyota_Yaris_Hatchback


@dataclass(frozen=True, init=False)
class TrashBin240LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TrashBin_240L


@dataclass(frozen=True, init=False)
class TrashCanRnd130LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TrashCan_Rnd_130L


@dataclass(frozen=True, init=False)
class TrashCanSqr160LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TrashCan_Sqr_160L


@dataclass(frozen=True, init=False)
class TriangleParkingSpaceLockEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TriangleParkingSpaceLock


@dataclass(frozen=True, init=False)
class TurkishHazel10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TurkishHazel10y


@dataclass(frozen=True, init=False)
class TurkishHazel20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TurkishHazel20y


@dataclass(frozen=True, init=False)
class USPoliceVolvoXC60Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.US_Police_Volvo_XC60


@dataclass(frozen=True, init=False)
class VehicleSignal30cmFLJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_FL_JP


@dataclass(frozen=True, init=False)
class VehicleSignal30cmFRJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_FR_JP


@dataclass(frozen=True, init=False)
class VehicleSignal30cmFJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_F_JP


@dataclass(frozen=True, init=False)
class VehicleSignal30cmLJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_L_JP


@dataclass(frozen=True, init=False)
class VehicleSignal30cmRJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_R_JP


@dataclass(frozen=True, init=False)
class VehicleSignalGreen30cmJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignalGreen30cm_JP


@dataclass(frozen=True, init=False)
class VehicleSignalOrange30cmJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignalOrange30cm_JP


@dataclass(frozen=True, init=False)
class VehicleSignalRed30cmJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignalRed30cm_JP


@dataclass(frozen=True, init=False)
class VolvoFH16Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Volvo_FH16


@dataclass(frozen=True, init=False)
class VolvoXC60Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Volvo_XC60


@dataclass(frozen=True, init=False)
class WarehouseEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Warehouse


@dataclass(frozen=True, init=False)
class WheatAEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wheat_A


@dataclass(frozen=True, init=False)
class WheatBEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wheat_B


@dataclass(frozen=True, init=False)
class WheatCEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wheat_C


@dataclass(frozen=True, init=False)
class WheelieBin1100LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.WheelieBin_1100L


@dataclass(frozen=True, init=False)
class WindmillEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Windmill


@dataclass(frozen=True, init=False)
class WulingHongguangEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wuling_Hongguang


@dataclass(frozen=True, init=False)
class ChurchEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Church


@dataclass(frozen=True, init=False)
class FactoryEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Factory


@dataclass(frozen=True, init=False)
class ConcreteGuardrailEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ConcreteGuardrail


@dataclass(frozen=True, init=False)
class GuardrailEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Guardrail


@dataclass(frozen=True, init=False)
class FenceEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Fence


@dataclass(frozen=True, init=False)
class LinePlacedRoadImperfectionEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.LinePlacedRoadImperfection


@dataclass(frozen=True, init=False)
class SoundAbsorbingWallEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SoundAbsorbingWall


@dataclass(frozen=True, init=False)
class WallEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wall


@dataclass(frozen=True, init=False)
class HouseEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.House


@dataclass(frozen=True, init=False)
class OfficeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Office


@dataclass(frozen=True, init=False)
class BoxEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Box


@dataclass(frozen=True, init=False)
class CapsuleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Capsule


@dataclass(frozen=True, init=False)
class ConeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cone


@dataclass(frozen=True, init=False)
class CylinderEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cylinder


@dataclass(frozen=True, init=False)
class SphereEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Sphere


@dataclass(frozen=True, init=False)
class TripodEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Tripod


@dataclass(frozen=True, init=False)
class TrafficSignPoleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TrafficSignPole
