from abc import abstractmethod
from dataclasses import dataclass, field

import numpy as np
from symaware.base import Entity as BaseEntity
from symaware.base import NullDynamicalModel

from ._symaware_prescan import (
    Orientation,
    Position,
    SensorDetectability,
    _Entity,
    _Experiment,
    _WorldObject,
    ObjectType,
)
from .dynamical_model import DynamicalModel


@dataclass(frozen=True)
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
    _internal_entity:
        Internal entity object used by the Prescan simulator's python bindings. Do not initialise this object directly.
    """

    model: DynamicalModel = field(default_factory=NullDynamicalModel)
    position: Position = field(default_factory=Position)
    orientation: Orientation = field(default_factory=Orientation)
    cog_offset: Position = field(default_factory=Position)
    is_collision_detectable: bool = True
    is_movable: bool = True
    sensor_detectability: SensorDetectability = SensorDetectability.SensorDetectabilityDetectable
    _internal_entity: _Entity = None  # type: ignore

    def __post_init__(self):
        if isinstance(self.position, np.ndarray):
            object.__setattr__(self, "position", Position(self.position))
        if isinstance(self.orientation, np.ndarray):
            object.__setattr__(self, "orientation", Orientation(self.orientation))
        if isinstance(self.cog_offset, np.ndarray):
            object.__setattr__(self, "cog_offset", Position(self.cog_offset))
        entity_model = None if isinstance(self.model, NullDynamicalModel) else self.model.internal_model
        if self._internal_entity is None:
            object.__setattr__(
                self,
                "_internal_entity",
                _Entity(
                    object_type=self.object_type,
                    setup=_Entity.Setup(
                        position=self.position,
                        orientation=self.orientation,
                        cog_offset=self.cog_offset,
                        is_collision_detectable=self.is_collision_detectable,
                        is_movable=self.is_movable,
                        sensor_detectability=self.sensor_detectability,
                    ),
                    entity_model=entity_model,  # type: ignore
                ),
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


@dataclass(frozen=True)
class ADACtargetyellowmercEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ADAC_target_yellow_merc


@dataclass(frozen=True)
class ApartmentBuildingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ApartmentBuilding


@dataclass(frozen=True)
class ArrowBoardTrailerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ArrowBoard_Trailer


@dataclass(frozen=True)
class Ash10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Ash10y


@dataclass(frozen=True)
class Ash20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Ash20y


@dataclass(frozen=True)
class AudiA3Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Audi_A3


@dataclass(frozen=True)
class AudiA8SedanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Audi_A8_Sedan


@dataclass(frozen=True)
class AustrianPine10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.AustrianPine10y


@dataclass(frozen=True)
class AustrianPine20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.AustrianPine20y


@dataclass(frozen=True)
class BEPoliceVolvoXC60Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BE_Police_Volvo_XC60


@dataclass(frozen=True)
class BMWX5SUVEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BMW_X5_SUV


@dataclass(frozen=True)
class BMWZ3ConvertibleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BMW_Z3_Convertible


@dataclass(frozen=True)
class BalloonCarEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BalloonCar


@dataclass(frozen=True)
class BarrierFenceEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BarrierFence


@dataclass(frozen=True)
class Birch10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Birch10y


@dataclass(frozen=True)
class Birch20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Birch20y


@dataclass(frozen=True)
class BlueSpruce10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BlueSpruce10y


@dataclass(frozen=True)
class BlueSpruce20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BlueSpruce20y


@dataclass(frozen=True)
class BottsDotsWhiteEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BottsDots_White


@dataclass(frozen=True)
class BottsDotsYellowEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.BottsDots_Yellow


@dataclass(frozen=True)
class Boy100Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Boy_100


@dataclass(frozen=True)
class Boy150Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Boy_150


@dataclass(frozen=True)
class Building00AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_00A


@dataclass(frozen=True)
class Building01AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_01A


@dataclass(frozen=True)
class Building02AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_02A


@dataclass(frozen=True)
class Building03AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_03A


@dataclass(frozen=True)
class Building04AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_04A


@dataclass(frozen=True)
class Building05AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_05A


@dataclass(frozen=True)
class Building06AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_06A


@dataclass(frozen=True)
class Building07AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_07A


@dataclass(frozen=True)
class Building08AEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Building_08A


@dataclass(frozen=True)
class BusstopEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Busstop


@dataclass(frozen=True)
class CAT725Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CAT_725


@dataclass(frozen=True)
class CadillacEscaladeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cadillac_Escalade


@dataclass(frozen=True)
class CarDealerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CarDealer


@dataclass(frozen=True)
class CarTrailerSmallEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Car_Trailer_Small


@dataclass(frozen=True)
class CatsEyesREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesR


@dataclass(frozen=True)
class CatsEyesWEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesW


@dataclass(frozen=True)
class CatsEyesWREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesWR


@dataclass(frozen=True)
class CatsEyesWYEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesWY


@dataclass(frozen=True)
class CatsEyesYEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CatsEyesY


@dataclass(frozen=True)
class ChildLeaningEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Child_Leaning


@dataclass(frozen=True)
class ChildOverweightEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Child_Overweight


@dataclass(frozen=True)
class ChildRegularEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Child_Regular


@dataclass(frozen=True)
class ChildSittingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Child_Sitting


@dataclass(frozen=True)
class CinderBlockAEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CinderBlock_A


@dataclass(frozen=True)
class CinderBlockBEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CinderBlock_B


@dataclass(frozen=True)
class CinderBlockCEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CinderBlock_C


@dataclass(frozen=True)
class CitroenC3HatchbackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Citroen_C3_Hatchback


@dataclass(frozen=True)
class ConstructionSignJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ConstructionSign_JP


@dataclass(frozen=True)
class ContainerTrailerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Container_Trailer


@dataclass(frozen=True)
class CornerReflector138mmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CornerReflector138mm


@dataclass(frozen=True)
class CornerReflector1768mmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CornerReflector176_8mm


@dataclass(frozen=True)
class CornerReflector4635mmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.CornerReflector46_35mm


@dataclass(frozen=True)
class CottonAEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cotton_A


@dataclass(frozen=True)
class CottonBEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cotton_B


@dataclass(frozen=True)
class CottonCEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cotton_C


@dataclass(frozen=True)
class DAF95XFEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.DAF_95_XF


@dataclass(frozen=True)
class DAFEuro6XFEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.DAF_Euro_6_XF


@dataclass(frozen=True)
class DeerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Deer


@dataclass(frozen=True)
class Dogwood10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Dogwood10y


@dataclass(frozen=True)
class Dogwood20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Dogwood20y


@dataclass(frozen=True)
class Dumpster2300LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Dumpster_2300L


@dataclass(frozen=True)
class DutchChurchEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.DutchChurch


@dataclass(frozen=True)
class EmptyLightNodeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Empty_Light_Node


@dataclass(frozen=True)
class ExistingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Existing


@dataclass(frozen=True)
class FAWJiefangJ6MEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FAW_Jiefang_J6M


@dataclass(frozen=True)
class FShape150cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FShape150cm


@dataclass(frozen=True)
class FShape250cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FShape250cm


@dataclass(frozen=True)
class FShape350cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FShape350cm


@dataclass(frozen=True)
class FemaleBendingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_Bending


@dataclass(frozen=True)
class FemaleLeaningEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_Leaning


@dataclass(frozen=True)
class FemaleOverweightEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_Overweight


@dataclass(frozen=True)
class FemaleRegularEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_Regular


@dataclass(frozen=True)
class FemalewBuggyEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_wBuggy


@dataclass(frozen=True)
class FemalewLongCoatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_wLongCoat


@dataclass(frozen=True)
class FemalewRaincoatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_wRaincoat


@dataclass(frozen=True)
class FemalewShoppingCartEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Female_wShoppingCart


@dataclass(frozen=True)
class FiatBravoHatchbackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Fiat_Bravo_Hatchback


@dataclass(frozen=True)
class FireBrigadeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.FireBrigade


@dataclass(frozen=True)
class FordFiestaHatchbackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Ford_Fiesta_Hatchback


@dataclass(frozen=True)
class FordFocusStationwagonEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Ford_Focus_Stationwagon


@dataclass(frozen=True)
class FullTrailerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Full_Trailer


@dataclass(frozen=True)
class GarageGroundFloorEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Garage_Ground_Floor


@dataclass(frozen=True)
class GarageMidFloorEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Garage_Mid_Floor


@dataclass(frozen=True)
class GarageTopFloorEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Garage_Top_Floor


@dataclass(frozen=True)
class GasStationEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GasStation


@dataclass(frozen=True)
class GenesisGV80Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Genesis_GV80


@dataclass(frozen=True)
class GuardrailReflectorRectREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RectR


@dataclass(frozen=True)
class GuardrailReflectorRectWEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RectW


@dataclass(frozen=True)
class GuardrailReflectorRectWREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RectWR


@dataclass(frozen=True)
class GuardrailReflectorRoundREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RoundR


@dataclass(frozen=True)
class GuardrailReflectorRoundWEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RoundW


@dataclass(frozen=True)
class GuardrailReflectorRoundWREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RoundWR


@dataclass(frozen=True)
class GuardrailReflectorRoundYEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuardrailReflector_RoundY


@dataclass(frozen=True)
class GuidedSoftTargetEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.GuidedSoftTarget


@dataclass(frozen=True)
class HOWOT5GCementTruckEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HOWO_T5G_Cement_Truck


@dataclass(frozen=True)
class HinoBlueRibbonEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Hino_Blue_Ribbon


@dataclass(frozen=True)
class HondaPanEuropeanMotorcycleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Honda_Pan_European_Motorcycle


@dataclass(frozen=True)
class HondaPanEuropeanMotorcycleWithDriverEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Honda_Pan_European_Motorcycle_With_Driver


@dataclass(frozen=True)
class HouseModernEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseModern


@dataclass(frozen=True)
class HouseOld1Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld1


@dataclass(frozen=True)
class HouseOld2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld2


@dataclass(frozen=True)
class HouseOld3Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld3


@dataclass(frozen=True)
class HouseOld4Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld4


@dataclass(frozen=True)
class HouseOld5Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld5


@dataclass(frozen=True)
class HouseOld6Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.HouseOld6


@dataclass(frozen=True)
class Houses1930sEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Houses1930s


@dataclass(frozen=True)
class HyundaiIoniq5Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Hyundai_Ioniq5


@dataclass(frozen=True)
class Hyundaii30NLineEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Hyundai_i30_NLine


@dataclass(frozen=True)
class IsuzuDMaxEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Isuzu_DMax


@dataclass(frozen=True)
class IsuzuGigaFireTruckEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Isuzu_Giga_Fire_Truck


@dataclass(frozen=True)
class JACHFCSeriesEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.JAC_HFC_Series


@dataclass(frozen=True)
class JapaneseMaple10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.JapaneseMaple10y


@dataclass(frozen=True)
class JapaneseMaple20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.JapaneseMaple20y


@dataclass(frozen=True)
class JobyAviationS4Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Joby_Aviation_S4


@dataclass(frozen=True)
class KiaEV6Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Kia_EV6


@dataclass(frozen=True)
class KiaEV6wRoofRackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Kia_EV6_wRoofRack


@dataclass(frozen=True)
class KiaEV6wRoofRackSiemensEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Kia_EV6_wRoofRack_Siemens


@dataclass(frozen=True)
class LexusGS450hFSportSedanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Lexus_GS_450h_F_Sport_Sedan


@dataclass(frozen=True)
class LexusLS600hFSportEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Lexus_LS_600h_F_Sport


@dataclass(frozen=True)
class LightPostEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.LightPost


@dataclass(frozen=True)
class Lilac10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Lilac10y


@dataclass(frozen=True)
class Lilac20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Lilac20y


@dataclass(frozen=True)
class Magnolia10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Magnolia10y


@dataclass(frozen=True)
class Magnolia20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Magnolia20y


@dataclass(frozen=True)
class Male200Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_200


@dataclass(frozen=True)
class MaleAfricanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_African


@dataclass(frozen=True)
class MaleBendingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Bending


@dataclass(frozen=True)
class MaleBendingOverEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_BendingOver


@dataclass(frozen=True)
class MaleCyclingCyclistEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_CyclingCyclist


@dataclass(frozen=True)
class MaleFemaleHandInHandEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Female_HandInHand


@dataclass(frozen=True)
class MaleLargeShoulderSuitcaseEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_LargeShoulderSuitcase


@dataclass(frozen=True)
class MaleLeaningEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Leaning


@dataclass(frozen=True)
class MaleLeaningBackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_LeaningBack


@dataclass(frozen=True)
class MaleLyingDownEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_LyingDown


@dataclass(frozen=True)
class MaleOldWhiteWithStickEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Old_White_WithStick


@dataclass(frozen=True)
class MaleOldWhiteWithWalkerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Old_White_WithWalker


@dataclass(frozen=True)
class MaleOldWhiteWithWalkerWithWheelsEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Old_White_WithWalkerWithWheels


@dataclass(frozen=True)
class MaleOverweightEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Overweight


@dataclass(frozen=True)
class MaleRegularEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Regular


@dataclass(frozen=True)
class MaleShoppingBagEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_ShoppingBag


@dataclass(frozen=True)
class MaleSittingEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_Sitting


@dataclass(frozen=True)
class MalewBackpackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wBackpack


@dataclass(frozen=True)
class MalewBicycleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wBicycle


@dataclass(frozen=True)
class MalewLargeBackpackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wLargeBackpack


@dataclass(frozen=True)
class MalewLongCoatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wLongCoat


@dataclass(frozen=True)
class MalewRaincoatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wRaincoat


@dataclass(frozen=True)
class MalewSuitEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wSuit


@dataclass(frozen=True)
class MalewSuitcaseEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Male_wSuitcase


@dataclass(frozen=True)
class Man250Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Man_250


@dataclass(frozen=True)
class ManAsianEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Man_Asian


@dataclass(frozen=True)
class MazdaRX8CoupeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Mazda_RX8_Coupe


@dataclass(frozen=True)
class MercedesBenzActros1851LS4x2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.MercedesBenz_Actros_1851_LS_4x2


@dataclass(frozen=True)
class MercedesBenzActros1860LS4x2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.MercedesBenz_Actros_1860_LS_4x2


@dataclass(frozen=True)
class MercedesBenzActros2541L6x2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.MercedesBenz_Actros_2541_L_6x2


@dataclass(frozen=True)
class MitsubishiOutlanderPHEVEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Mitsubishi_Outlander_PHEV


@dataclass(frozen=True)
class MonumentEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Monument


@dataclass(frozen=True)
class NCAPAdultEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Adult


@dataclass(frozen=True)
class NCAPChildEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Child


@dataclass(frozen=True)
class NCAPCyclistEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Cyclist


@dataclass(frozen=True)
class NCAPEBTAEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_EBTA


@dataclass(frozen=True)
class NCAPGVTEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_GVT


@dataclass(frozen=True)
class NCAPMotorcycleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Motorcycle


@dataclass(frozen=True)
class NCAPScooterEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_Scooter


@dataclass(frozen=True)
class NCAPStreetLightEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NCAP_StreetLight


@dataclass(frozen=True)
class NLAmbulanceVolvoXC60Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.NL_Ambulance_Volvo_XC60


@dataclass(frozen=True)
class NissanAriyaEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Nissan_Ariya


@dataclass(frozen=True)
class NissanCabstarBoxtruckEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Nissan_Cabstar_Boxtruck


@dataclass(frozen=True)
class OfficeBrownFlatEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OfficeBrownFlat


@dataclass(frozen=True)
class OfficeBrownTall1Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OfficeBrownTall1


@dataclass(frozen=True)
class OfficeBrownTall2Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OfficeBrownTall2


@dataclass(frozen=True)
class OfficeGreenTallEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OfficeGreenTall


@dataclass(frozen=True)
class Overhang1LightJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Light_JP


@dataclass(frozen=True)
class Overhang1LightKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Light_KR


@dataclass(frozen=True)
class Overhang1LightNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Light_NL


@dataclass(frozen=True)
class Overhang1LightUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Light_US


@dataclass(frozen=True)
class Overhang1PostJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Post_JP


@dataclass(frozen=True)
class Overhang1PostKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Post_KR


@dataclass(frozen=True)
class Overhang1PostNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Post_NL


@dataclass(frozen=True)
class Overhang1PostUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang1Post_US


@dataclass(frozen=True)
class Overhang2LightsJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Lights_JP


@dataclass(frozen=True)
class Overhang2LightsKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Lights_KR


@dataclass(frozen=True)
class Overhang2LightsNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Lights_NL


@dataclass(frozen=True)
class Overhang2LightsUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Lights_US


@dataclass(frozen=True)
class Overhang2PostJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Post_JP


@dataclass(frozen=True)
class Overhang2PostKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Post_KR


@dataclass(frozen=True)
class Overhang2PostNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Post_NL


@dataclass(frozen=True)
class Overhang2PostUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Overhang2Post_US


@dataclass(frozen=True)
class OverhangDH2LightsUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OverhangDH2Lights_US


@dataclass(frozen=True)
class OverhangDHPostUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.OverhangDHPost_US


@dataclass(frozen=True)
class PalletEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Pallet


@dataclass(frozen=True)
class PedestrianSignalJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PedestrianSignal_JP


@dataclass(frozen=True)
class Peterbilt579Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Peterbilt_579


@dataclass(frozen=True)
class Peterbilt579TrailerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Peterbilt_579_Trailer


@dataclass(frozen=True)
class PlasticBarrier100cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PlasticBarrier100cm


@dataclass(frozen=True)
class PrismSignV305070Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSignV_30_50_70


@dataclass(frozen=True)
class PrismSignV51015Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSignV_5_10_15


@dataclass(frozen=True)
class PrismSignV80100110Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSignV_80_100_110


@dataclass(frozen=True)
class PrismSign305070Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSign_30_50_70


@dataclass(frozen=True)
class PrismSign51015Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSign_5_10_15


@dataclass(frozen=True)
class PrismSign80100110Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.PrismSign_80_100_110


@dataclass(frozen=True)
class Pylon01Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Pylon_01


@dataclass(frozen=True)
class Pylon02Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Pylon_02


@dataclass(frozen=True)
class ReflectorSignEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ReflectorSign


@dataclass(frozen=True)
class ReflectorSignSimpleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ReflectorSignSimple


@dataclass(frozen=True)
class RivianR1TEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Rivian_R1T


@dataclass(frozen=True)
class RivianR1TwCoverEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Rivian_R1T_wCover


@dataclass(frozen=True)
class RoadClosedwLightsEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadClosed_wLights


@dataclass(frozen=True)
class RoadsideLightNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadsideLight_NL


@dataclass(frozen=True)
class RoadsideMarkerEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadsideMarker


@dataclass(frozen=True)
class RoadsidePostEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadsidePost


@dataclass(frozen=True)
class RoadsidePostNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.RoadsidePost_NL


@dataclass(frozen=True)
class Roewe550SSedanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Roewe_550_S_Sedan


@dataclass(frozen=True)
class RowCropTractorEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Row_Crop_Tractor


@dataclass(frozen=True)
class SchoolEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.School


@dataclass(frozen=True)
class ScooterEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Scooter


@dataclass(frozen=True)
class ScooterwBoxEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Scooter_wBox


@dataclass(frozen=True)
class Serviceberry10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Serviceberry10y


@dataclass(frozen=True)
class Serviceberry15yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Serviceberry15y


@dataclass(frozen=True)
class Serviceberry5yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Serviceberry5y


@dataclass(frozen=True)
class ShoppingCartEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ShoppingCart


@dataclass(frozen=True)
class SiemenseRodEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Siemens_eRod


@dataclass(frozen=True)
class SignalCasing20cmNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing20cm_NL


@dataclass(frozen=True)
class SignalCasing30cmDHUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing30cmDH_US


@dataclass(frozen=True)
class SignalCasing30cmJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing30cm_JP


@dataclass(frozen=True)
class SignalCasing30cmNLEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing30cm_NL


@dataclass(frozen=True)
class SignalCasing30cmUSEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing30cm_US


@dataclass(frozen=True)
class SignalCasing330cmKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing3_30cm_KR


@dataclass(frozen=True)
class SignalCasing430cmKREntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SignalCasing4_30cm_KR


@dataclass(frozen=True)
class SkywellEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Skywell


@dataclass(frozen=True)
class SpeedBump250cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpeedBump250cm


@dataclass(frozen=True)
class SpeedBump350cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpeedBump350cm


@dataclass(frozen=True)
class SportsBikeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Sports_Bike


@dataclass(frozen=True)
class SportsBikewDriverEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Sports_Bike_wDriver


@dataclass(frozen=True)
class SpringPost46cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpringPost46cm


@dataclass(frozen=True)
class SpringPost75cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpringPost75cm


@dataclass(frozen=True)
class SpringPost95cmEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SpringPost95cm


@dataclass(frozen=True)
class SuzukiHustlerHybridEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Suzuki_Hustler_Hybrid


@dataclass(frozen=True)
class TerracedHousesEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TerracedHouses


@dataclass(frozen=True)
class TeslaModel3Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Tesla_Model_3


@dataclass(frozen=True)
class TireHorizontalEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Tire_Horizontal


@dataclass(frozen=True)
class TireVerticalEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Tire_Vertical


@dataclass(frozen=True)
class Toddler050Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Toddler_050


@dataclass(frozen=True)
class ToyotaPreviaMPVEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Toyota_Previa_MPV


@dataclass(frozen=True)
class ToyotaPriusSedanEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Toyota_Prius_Sedan


@dataclass(frozen=True)
class ToyotaYarisHatchbackEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Toyota_Yaris_Hatchback


@dataclass(frozen=True)
class TrashBin240LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TrashBin_240L


@dataclass(frozen=True)
class TrashCanRnd130LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TrashCan_Rnd_130L


@dataclass(frozen=True)
class TrashCanSqr160LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TrashCan_Sqr_160L


@dataclass(frozen=True)
class TriangleParkingSpaceLockEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TriangleParkingSpaceLock


@dataclass(frozen=True)
class TurkishHazel10yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TurkishHazel10y


@dataclass(frozen=True)
class TurkishHazel20yEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TurkishHazel20y


@dataclass(frozen=True)
class USPoliceVolvoXC60Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.US_Police_Volvo_XC60


@dataclass(frozen=True)
class VehicleSignal30cmFLJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_FL_JP


@dataclass(frozen=True)
class VehicleSignal30cmFRJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_FR_JP


@dataclass(frozen=True)
class VehicleSignal30cmFJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_F_JP


@dataclass(frozen=True)
class VehicleSignal30cmLJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_L_JP


@dataclass(frozen=True)
class VehicleSignal30cmRJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignal30cm_R_JP


@dataclass(frozen=True)
class VehicleSignalGreen30cmJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignalGreen30cm_JP


@dataclass(frozen=True)
class VehicleSignalOrange30cmJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignalOrange30cm_JP


@dataclass(frozen=True)
class VehicleSignalRed30cmJPEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.VehicleSignalRed30cm_JP


@dataclass(frozen=True)
class VolvoFH16Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Volvo_FH16


@dataclass(frozen=True)
class VolvoXC60Entity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Volvo_XC60


@dataclass(frozen=True)
class WarehouseEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Warehouse


@dataclass(frozen=True)
class WheatAEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wheat_A


@dataclass(frozen=True)
class WheatBEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wheat_B


@dataclass(frozen=True)
class WheatCEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wheat_C


@dataclass(frozen=True)
class WheelieBin1100LEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.WheelieBin_1100L


@dataclass(frozen=True)
class WindmillEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Windmill


@dataclass(frozen=True)
class WulingHongguangEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wuling_Hongguang


@dataclass(frozen=True)
class ChurchEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Church


@dataclass(frozen=True)
class FactoryEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Factory


@dataclass(frozen=True)
class ConcreteGuardrailEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.ConcreteGuardrail


@dataclass(frozen=True)
class GuardrailEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Guardrail


@dataclass(frozen=True)
class FenceEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Fence


@dataclass(frozen=True)
class LinePlacedRoadImperfectionEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.LinePlacedRoadImperfection


@dataclass(frozen=True)
class SoundAbsorbingWallEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.SoundAbsorbingWall


@dataclass(frozen=True)
class WallEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Wall


@dataclass(frozen=True)
class HouseEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.House


@dataclass(frozen=True)
class OfficeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Office


@dataclass(frozen=True)
class BoxEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Box


@dataclass(frozen=True)
class CapsuleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Capsule


@dataclass(frozen=True)
class ConeEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cone


@dataclass(frozen=True)
class CylinderEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Cylinder


@dataclass(frozen=True)
class SphereEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Sphere


@dataclass(frozen=True)
class TripodEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.Tripod


@dataclass(frozen=True)
class TrafficSignPoleEntity(Entity):
    @property
    def object_type(self) -> ObjectType:
        return ObjectType.TrafficSignPole
