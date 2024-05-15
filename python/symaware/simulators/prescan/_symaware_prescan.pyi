"""
Python binding for the symaware prescan library
"""

from __future__ import annotations

import typing

import numpy

__all__ = [
    "Acceleration",
    "AngularVelocity",
    "AsphaltTone",
    "AsphaltToneDark",
    "AsphaltToneDarker",
    "AsphaltToneLight",
    "AsphaltToneLighter",
    "AsphaltToneStandard",
    "AsphaltType",
    "AsphaltTypeColoredTexture",
    "AsphaltTypeSingleColor",
    "AsphaltTypeStandard",
    "Forward",
    "Gear",
    "LaneSideType",
    "LaneSideTypeInner",
    "LaneSideTypeOuter",
    "LaneType",
    "LaneTypeBiking",
    "LaneTypeDriving",
    "LaneTypeSideWalk",
    "LogLevel",
    "LogLevelClean",
    "LogLevelCrawl",
    "LogLevelCritical",
    "LogLevelDebug",
    "LogLevelError",
    "LogLevelInfo",
    "LogLevelInherit",
    "LogLevelNotice",
    "LogLevelOff",
    "LogLevelWarning",
    "Neutral",
    "ObjectType",
    "Orientation",
    "ParamPolyRangeTypeArcLength",
    "ParamPolyRangeTypeNormalized",
    "ParameterRange",
    "Position",
    "Reverse",
    "Road",
    "RoadSideType",
    "RoadSideTypeLeft",
    "RoadSideTypeRight",
    "SensorDetectability",
    "SensorDetectabilityDetectable",
    "SensorDetectabilityInvisible",
    "SensorDetectabilityOccluding",
    "SensorType",
    "SimulationSpeed",
    "SimulationSpeedAsFastAsPossible",
    "SimulationSpeedHalfWallClockTime",
    "SimulationSpeedQuarterWallClockTime",
    "SimulationSpeedWallClockTime",
    "SkyLightPollution",
    "SkyLightPollutionBrightSuburban",
    "SkyLightPollutionCity",
    "SkyLightPollutionDarkSite",
    "SkyLightPollutionInnerCity",
    "SkyLightPollutionNone",
    "SkyLightPollutionRural",
    "SkyLightPollutionRuralSuburban",
    "SkyLightPollutionSuburban",
    "SkyLightPollutionSuburbanUrban",
    "SkyType",
    "TrafficSide",
    "TrafficSideTypeLeftHandTraffic",
    "TrafficSideTypeRightHandTraffic",
    "Undefined",
    "Velocity",
    "WeatherType",
]

class Acceleration:
    x: float
    y: float
    z: float
    def __array__(self) -> numpy.ndarray[numpy.float64]: ...
    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, x: float, y: float, z: float) -> None: ...
    @typing.overload
    def __init__(self, zero_init: bool) -> None:
        """
        Initialise with zeros or with NaNs
        """

    @typing.overload
    def __init__(self, array: numpy.ndarray[numpy.float64]) -> None: ...
    def __repr__(self) -> str: ...

class AngularVelocity:
    pitch: float
    roll: float
    yaw: float
    def __array__(self) -> numpy.ndarray[numpy.float64]: ...
    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, roll: float, pitch: float, yaw: float) -> None: ...
    @typing.overload
    def __init__(self, zero_init: bool) -> None:
        """
        Initialise with zeros or with NaNs
        """

    @typing.overload
    def __init__(self, array: numpy.ndarray[numpy.float64]) -> None: ...
    def __repr__(self) -> str: ...

class AsphaltTone:
    """
    Members:

      AsphaltToneDark

      AsphaltToneDarker

      AsphaltToneLight

      AsphaltToneLighter

      AsphaltToneStandard
    """

    AsphaltToneDark: typing.ClassVar[AsphaltTone]  # value = <AsphaltTone.AsphaltToneDark: 1>
    AsphaltToneDarker: typing.ClassVar[AsphaltTone]  # value = <AsphaltTone.AsphaltToneDarker: 2>
    AsphaltToneLight: typing.ClassVar[AsphaltTone]  # value = <AsphaltTone.AsphaltToneLight: 3>
    AsphaltToneLighter: typing.ClassVar[AsphaltTone]  # value = <AsphaltTone.AsphaltToneLighter: 4>
    AsphaltToneStandard: typing.ClassVar[AsphaltTone]  # value = <AsphaltTone.AsphaltToneStandard: 0>
    __members__: typing.ClassVar[
        dict[str, AsphaltTone]
    ]  # value = {'AsphaltToneDark': <AsphaltTone.AsphaltToneDark: 1>, 'AsphaltToneDarker': <AsphaltTone.AsphaltToneDarker: 2>, 'AsphaltToneLight': <AsphaltTone.AsphaltToneLight: 3>, 'AsphaltToneLighter': <AsphaltTone.AsphaltToneLighter: 4>, 'AsphaltToneStandard': <AsphaltTone.AsphaltToneStandard: 0>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class AsphaltType:
    """
    Members:

      AsphaltTypeColoredTexture

      AsphaltTypeSingleColor

      AsphaltTypeStandard
    """

    AsphaltTypeColoredTexture: typing.ClassVar[AsphaltType]  # value = <AsphaltType.AsphaltTypeColoredTexture: 2>
    AsphaltTypeSingleColor: typing.ClassVar[AsphaltType]  # value = <AsphaltType.AsphaltTypeSingleColor: 1>
    AsphaltTypeStandard: typing.ClassVar[AsphaltType]  # value = <AsphaltType.AsphaltTypeStandard: 0>
    __members__: typing.ClassVar[
        dict[str, AsphaltType]
    ]  # value = {'AsphaltTypeColoredTexture': <AsphaltType.AsphaltTypeColoredTexture: 2>, 'AsphaltTypeSingleColor': <AsphaltType.AsphaltTypeSingleColor: 1>, 'AsphaltTypeStandard': <AsphaltType.AsphaltTypeStandard: 0>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class Gear:
    """
    Members:

      Forward : Forward gear

      Neutral : Neutral gear

      Reverse : Reverse gear

      Undefined : Undefined gear. Won't change the gear.
    """

    Forward: typing.ClassVar[Gear]  # value = <Gear.Forward: 1>
    Neutral: typing.ClassVar[Gear]  # value = <Gear.Neutral: 0>
    Reverse: typing.ClassVar[Gear]  # value = <Gear.Reverse: -1>
    Undefined: typing.ClassVar[Gear]  # value = <Gear.Undefined: 2>
    __members__: typing.ClassVar[
        dict[str, Gear]
    ]  # value = {'Forward': <Gear.Forward: 1>, 'Neutral': <Gear.Neutral: 0>, 'Reverse': <Gear.Reverse: -1>, 'Undefined': <Gear.Undefined: 2>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class LaneSideType:
    """
    Members:

      LaneSideTypeInner

      LaneSideTypeOuter
    """

    LaneSideTypeInner: typing.ClassVar[LaneSideType]  # value = <LaneSideType.LaneSideTypeInner: 0>
    LaneSideTypeOuter: typing.ClassVar[LaneSideType]  # value = <LaneSideType.LaneSideTypeOuter: 1>
    __members__: typing.ClassVar[
        dict[str, LaneSideType]
    ]  # value = {'LaneSideTypeInner': <LaneSideType.LaneSideTypeInner: 0>, 'LaneSideTypeOuter': <LaneSideType.LaneSideTypeOuter: 1>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class LaneType:
    """
    Members:

      LaneTypeDriving

      LaneTypeBiking

      LaneTypeSideWalk
    """

    LaneTypeBiking: typing.ClassVar[LaneType]  # value = <LaneType.LaneTypeBiking: 1>
    LaneTypeDriving: typing.ClassVar[LaneType]  # value = <LaneType.LaneTypeDriving: 0>
    LaneTypeSideWalk: typing.ClassVar[LaneType]  # value = <LaneType.LaneTypeSideWalk: 2>
    __members__: typing.ClassVar[
        dict[str, LaneType]
    ]  # value = {'LaneTypeDriving': <LaneType.LaneTypeDriving: 0>, 'LaneTypeBiking': <LaneType.LaneTypeBiking: 1>, 'LaneTypeSideWalk': <LaneType.LaneTypeSideWalk: 2>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class LogLevel:
    """
    Members:

      LogLevelClean

      LogLevelCrawl

      LogLevelCritical

      LogLevelDebug

      LogLevelError

      LogLevelInfo

      LogLevelInherit

      LogLevelNotice

      LogLevelOff

      LogLevelWarning
    """

    LogLevelClean: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelClean: 7>
    LogLevelCrawl: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelCrawl: 0>
    LogLevelCritical: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelCritical: 6>
    LogLevelDebug: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelDebug: 1>
    LogLevelError: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelError: 5>
    LogLevelInfo: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelInfo: 2>
    LogLevelInherit: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelInherit: 9>
    LogLevelNotice: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelNotice: 3>
    LogLevelOff: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelOff: 8>
    LogLevelWarning: typing.ClassVar[LogLevel]  # value = <LogLevel.LogLevelWarning: 4>
    __members__: typing.ClassVar[
        dict[str, LogLevel]
    ]  # value = {'LogLevelClean': <LogLevel.LogLevelClean: 7>, 'LogLevelCrawl': <LogLevel.LogLevelCrawl: 0>, 'LogLevelCritical': <LogLevel.LogLevelCritical: 6>, 'LogLevelDebug': <LogLevel.LogLevelDebug: 1>, 'LogLevelError': <LogLevel.LogLevelError: 5>, 'LogLevelInfo': <LogLevel.LogLevelInfo: 2>, 'LogLevelInherit': <LogLevel.LogLevelInherit: 9>, 'LogLevelNotice': <LogLevel.LogLevelNotice: 3>, 'LogLevelOff': <LogLevel.LogLevelOff: 8>, 'LogLevelWarning': <LogLevel.LogLevelWarning: 4>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class ObjectType:
    """
    Members:

      ADAC_target_yellow_merc

      ApartmentBuilding

      ArrowBoard_Trailer

      Ash10y

      Ash20y

      Audi_A3

      Audi_A8_Sedan

      AustrianPine10y

      AustrianPine20y

      BE_Police_Volvo_XC60

      BMW_X5_SUV

      BMW_Z3_Convertible

      BalloonCar

      BarrierFence

      Birch10y

      Birch20y

      BlueSpruce10y

      BlueSpruce20y

      BottsDots_White

      BottsDots_Yellow

      Boy_100

      Boy_150

      Building_00A

      Building_01A

      Building_02A

      Building_03A

      Building_04A

      Building_05A

      Building_06A

      Building_07A

      Building_08A

      Busstop

      CAT_725

      Cadillac_Escalade

      CarDealer

      Car_Trailer_Small

      CatsEyesR

      CatsEyesW

      CatsEyesWR

      CatsEyesWY

      CatsEyesY

      Child_Leaning

      Child_Overweight

      Child_Regular

      Child_Sitting

      CinderBlock_A

      CinderBlock_B

      CinderBlock_C

      Citroen_C3_Hatchback

      ConstructionSign_JP

      Container_Trailer

      CornerReflector138mm

      CornerReflector176_8mm

      CornerReflector46_35mm

      Cotton_A

      Cotton_B

      Cotton_C

      DAF_95_XF

      DAF_Euro_6_XF

      Deer

      Dogwood10y

      Dogwood20y

      Dumpster_2300L

      DutchChurch

      Empty_Light_Node

      Existing

      FAW_Jiefang_J6M

      FShape150cm

      FShape250cm

      FShape350cm

      Female_Bending

      Female_Leaning

      Female_Overweight

      Female_Regular

      Female_wBuggy

      Female_wLongCoat

      Female_wRaincoat

      Female_wShoppingCart

      Fiat_Bravo_Hatchback

      FireBrigade

      Ford_Fiesta_Hatchback

      Ford_Focus_Stationwagon

      Full_Trailer

      Garage_Ground_Floor

      Garage_Mid_Floor

      Garage_Top_Floor

      GasStation

      Genesis_GV80

      GuardrailReflector_RectR

      GuardrailReflector_RectW

      GuardrailReflector_RectWR

      GuardrailReflector_RoundR

      GuardrailReflector_RoundW

      GuardrailReflector_RoundWR

      GuardrailReflector_RoundY

      GuidedSoftTarget

      HOWO_T5G_Cement_Truck

      Hino_Blue_Ribbon

      Honda_Pan_European_Motorcycle

      Honda_Pan_European_Motorcycle_With_Driver

      HouseModern

      HouseOld1

      HouseOld2

      HouseOld3

      HouseOld4

      HouseOld5

      HouseOld6

      Houses1930s

      Hyundai_Ioniq5

      Hyundai_i30_NLine

      Isuzu_DMax

      Isuzu_Giga_Fire_Truck

      JAC_HFC_Series

      JapaneseMaple10y

      JapaneseMaple20y

      Joby_Aviation_S4

      Kia_EV6

      Kia_EV6_wRoofRack

      Kia_EV6_wRoofRack_Siemens

      Lexus_GS_450h_F_Sport_Sedan

      Lexus_LS_600h_F_Sport

      LightPost

      Lilac10y

      Lilac20y

      Magnolia10y

      Magnolia20y

      Male_200

      Male_African

      Male_Bending

      Male_BendingOver

      Male_CyclingCyclist

      Male_Female_HandInHand

      Male_LargeShoulderSuitcase

      Male_Leaning

      Male_LeaningBack

      Male_LyingDown

      Male_Old_White_WithStick

      Male_Old_White_WithWalker

      Male_Old_White_WithWalkerWithWheels

      Male_Overweight

      Male_Regular

      Male_ShoppingBag

      Male_Sitting

      Male_wBackpack

      Male_wBicycle

      Male_wLargeBackpack

      Male_wLongCoat

      Male_wRaincoat

      Male_wSuit

      Male_wSuitcase

      Man_250

      Man_Asian

      Mazda_RX8_Coupe

      MercedesBenz_Actros_1851_LS_4x2

      MercedesBenz_Actros_1860_LS_4x2

      MercedesBenz_Actros_2541_L_6x2

      Mitsubishi_Outlander_PHEV

      Monument

      NCAP_Adult

      NCAP_Child

      NCAP_Cyclist

      NCAP_EBTA

      NCAP_GVT

      NCAP_Motorcycle

      NCAP_Scooter

      NCAP_StreetLight

      NL_Ambulance_Volvo_XC60

      Nissan_Ariya

      Nissan_Cabstar_Boxtruck

      OfficeBrownFlat

      OfficeBrownTall1

      OfficeBrownTall2

      OfficeGreenTall

      Overhang1Light_JP

      Overhang1Light_KR

      Overhang1Light_NL

      Overhang1Light_US

      Overhang1Post_JP

      Overhang1Post_KR

      Overhang1Post_NL

      Overhang1Post_US

      Overhang2Lights_JP

      Overhang2Lights_KR

      Overhang2Lights_NL

      Overhang2Lights_US

      Overhang2Post_JP

      Overhang2Post_KR

      Overhang2Post_NL

      Overhang2Post_US

      OverhangDH2Lights_US

      OverhangDHPost_US

      Pallet

      PedestrianSignal_JP

      Peterbilt_579

      Peterbilt_579_Trailer

      PlasticBarrier100cm

      PrismSignV_30_50_70

      PrismSignV_5_10_15

      PrismSignV_80_100_110

      PrismSign_30_50_70

      PrismSign_5_10_15

      PrismSign_80_100_110

      Pylon_01

      Pylon_02

      ReflectorSign

      ReflectorSignSimple

      Rivian_R1T

      Rivian_R1T_wCover

      RoadClosed_wLights

      RoadsideLight_NL

      RoadsideMarker

      RoadsidePost

      RoadsidePost_NL

      Roewe_550_S_Sedan

      Row_Crop_Tractor

      School

      Scooter

      Scooter_wBox

      Serviceberry10y

      Serviceberry15y

      Serviceberry5y

      ShoppingCart

      Siemens_eRod

      SignalCasing20cm_NL

      SignalCasing30cmDH_US

      SignalCasing30cm_JP

      SignalCasing30cm_NL

      SignalCasing30cm_US

      SignalCasing3_30cm_KR

      SignalCasing4_30cm_KR

      Skywell

      SpeedBump250cm

      SpeedBump350cm

      Sports_Bike

      Sports_Bike_wDriver

      SpringPost46cm

      SpringPost75cm

      SpringPost95cm

      Suzuki_Hustler_Hybrid

      TerracedHouses

      Tesla_Model_3

      Tire_Horizontal

      Tire_Vertical

      Toddler_050

      Toyota_Previa_MPV

      Toyota_Prius_Sedan

      Toyota_Yaris_Hatchback

      TrashBin_240L

      TrashCan_Rnd_130L

      TrashCan_Sqr_160L

      TriangleParkingSpaceLock

      TurkishHazel10y

      TurkishHazel20y

      US_Police_Volvo_XC60

      VehicleSignal30cm_FL_JP

      VehicleSignal30cm_FR_JP

      VehicleSignal30cm_F_JP

      VehicleSignal30cm_L_JP

      VehicleSignal30cm_R_JP

      VehicleSignalGreen30cm_JP

      VehicleSignalOrange30cm_JP

      VehicleSignalRed30cm_JP

      Volvo_FH16

      Volvo_XC60

      Warehouse

      Wheat_A

      Wheat_B

      Wheat_C

      WheelieBin_1100L

      Windmill

      Wuling_Hongguang

      Church

      Factory

      ConcreteGuardrail

      Guardrail

      Fence

      LinePlacedRoadImperfection

      SoundAbsorbingWall

      Wall

      House

      Office

      Box

      Capsule

      Cone

      Cylinder

      Sphere

      Tripod

      TrafficSignPole
    """

    ADAC_target_yellow_merc: typing.ClassVar[ObjectType]  # value = <ObjectType.ADAC_target_yellow_merc: 0>
    ApartmentBuilding: typing.ClassVar[ObjectType]  # value = <ObjectType.ApartmentBuilding: 1>
    ArrowBoard_Trailer: typing.ClassVar[ObjectType]  # value = <ObjectType.ArrowBoard_Trailer: 2>
    Ash10y: typing.ClassVar[ObjectType]  # value = <ObjectType.Ash10y: 3>
    Ash20y: typing.ClassVar[ObjectType]  # value = <ObjectType.Ash20y: 4>
    Audi_A3: typing.ClassVar[ObjectType]  # value = <ObjectType.Audi_A3: 5>
    Audi_A8_Sedan: typing.ClassVar[ObjectType]  # value = <ObjectType.Audi_A8_Sedan: 6>
    AustrianPine10y: typing.ClassVar[ObjectType]  # value = <ObjectType.AustrianPine10y: 7>
    AustrianPine20y: typing.ClassVar[ObjectType]  # value = <ObjectType.AustrianPine20y: 8>
    BE_Police_Volvo_XC60: typing.ClassVar[ObjectType]  # value = <ObjectType.BE_Police_Volvo_XC60: 9>
    BMW_X5_SUV: typing.ClassVar[ObjectType]  # value = <ObjectType.BMW_X5_SUV: 10>
    BMW_Z3_Convertible: typing.ClassVar[ObjectType]  # value = <ObjectType.BMW_Z3_Convertible: 11>
    BalloonCar: typing.ClassVar[ObjectType]  # value = <ObjectType.BalloonCar: 12>
    BarrierFence: typing.ClassVar[ObjectType]  # value = <ObjectType.BarrierFence: 13>
    Birch10y: typing.ClassVar[ObjectType]  # value = <ObjectType.Birch10y: 14>
    Birch20y: typing.ClassVar[ObjectType]  # value = <ObjectType.Birch20y: 15>
    BlueSpruce10y: typing.ClassVar[ObjectType]  # value = <ObjectType.BlueSpruce10y: 16>
    BlueSpruce20y: typing.ClassVar[ObjectType]  # value = <ObjectType.BlueSpruce20y: 17>
    BottsDots_White: typing.ClassVar[ObjectType]  # value = <ObjectType.BottsDots_White: 18>
    BottsDots_Yellow: typing.ClassVar[ObjectType]  # value = <ObjectType.BottsDots_Yellow: 19>
    Box: typing.ClassVar[ObjectType]  # value = <ObjectType.Box: 281>
    Boy_100: typing.ClassVar[ObjectType]  # value = <ObjectType.Boy_100: 20>
    Boy_150: typing.ClassVar[ObjectType]  # value = <ObjectType.Boy_150: 21>
    Building_00A: typing.ClassVar[ObjectType]  # value = <ObjectType.Building_00A: 22>
    Building_01A: typing.ClassVar[ObjectType]  # value = <ObjectType.Building_01A: 23>
    Building_02A: typing.ClassVar[ObjectType]  # value = <ObjectType.Building_02A: 24>
    Building_03A: typing.ClassVar[ObjectType]  # value = <ObjectType.Building_03A: 25>
    Building_04A: typing.ClassVar[ObjectType]  # value = <ObjectType.Building_04A: 26>
    Building_05A: typing.ClassVar[ObjectType]  # value = <ObjectType.Building_05A: 27>
    Building_06A: typing.ClassVar[ObjectType]  # value = <ObjectType.Building_06A: 28>
    Building_07A: typing.ClassVar[ObjectType]  # value = <ObjectType.Building_07A: 29>
    Building_08A: typing.ClassVar[ObjectType]  # value = <ObjectType.Building_08A: 30>
    Busstop: typing.ClassVar[ObjectType]  # value = <ObjectType.Busstop: 31>
    CAT_725: typing.ClassVar[ObjectType]  # value = <ObjectType.CAT_725: 32>
    Cadillac_Escalade: typing.ClassVar[ObjectType]  # value = <ObjectType.Cadillac_Escalade: 33>
    Capsule: typing.ClassVar[ObjectType]  # value = <ObjectType.Capsule: 282>
    CarDealer: typing.ClassVar[ObjectType]  # value = <ObjectType.CarDealer: 34>
    Car_Trailer_Small: typing.ClassVar[ObjectType]  # value = <ObjectType.Car_Trailer_Small: 35>
    CatsEyesR: typing.ClassVar[ObjectType]  # value = <ObjectType.CatsEyesR: 36>
    CatsEyesW: typing.ClassVar[ObjectType]  # value = <ObjectType.CatsEyesW: 37>
    CatsEyesWR: typing.ClassVar[ObjectType]  # value = <ObjectType.CatsEyesWR: 38>
    CatsEyesWY: typing.ClassVar[ObjectType]  # value = <ObjectType.CatsEyesWY: 39>
    CatsEyesY: typing.ClassVar[ObjectType]  # value = <ObjectType.CatsEyesY: 40>
    Child_Leaning: typing.ClassVar[ObjectType]  # value = <ObjectType.Child_Leaning: 41>
    Child_Overweight: typing.ClassVar[ObjectType]  # value = <ObjectType.Child_Overweight: 42>
    Child_Regular: typing.ClassVar[ObjectType]  # value = <ObjectType.Child_Regular: 43>
    Child_Sitting: typing.ClassVar[ObjectType]  # value = <ObjectType.Child_Sitting: 44>
    Church: typing.ClassVar[ObjectType]  # value = <ObjectType.Church: 271>
    CinderBlock_A: typing.ClassVar[ObjectType]  # value = <ObjectType.CinderBlock_A: 45>
    CinderBlock_B: typing.ClassVar[ObjectType]  # value = <ObjectType.CinderBlock_B: 46>
    CinderBlock_C: typing.ClassVar[ObjectType]  # value = <ObjectType.CinderBlock_C: 47>
    Citroen_C3_Hatchback: typing.ClassVar[ObjectType]  # value = <ObjectType.Citroen_C3_Hatchback: 48>
    ConcreteGuardrail: typing.ClassVar[ObjectType]  # value = <ObjectType.ConcreteGuardrail: 273>
    Cone: typing.ClassVar[ObjectType]  # value = <ObjectType.Cone: 283>
    ConstructionSign_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.ConstructionSign_JP: 49>
    Container_Trailer: typing.ClassVar[ObjectType]  # value = <ObjectType.Container_Trailer: 50>
    CornerReflector138mm: typing.ClassVar[ObjectType]  # value = <ObjectType.CornerReflector138mm: 51>
    CornerReflector176_8mm: typing.ClassVar[ObjectType]  # value = <ObjectType.CornerReflector176_8mm: 52>
    CornerReflector46_35mm: typing.ClassVar[ObjectType]  # value = <ObjectType.CornerReflector46_35mm: 53>
    Cotton_A: typing.ClassVar[ObjectType]  # value = <ObjectType.Cotton_A: 54>
    Cotton_B: typing.ClassVar[ObjectType]  # value = <ObjectType.Cotton_B: 55>
    Cotton_C: typing.ClassVar[ObjectType]  # value = <ObjectType.Cotton_C: 56>
    Cylinder: typing.ClassVar[ObjectType]  # value = <ObjectType.Cylinder: 284>
    DAF_95_XF: typing.ClassVar[ObjectType]  # value = <ObjectType.DAF_95_XF: 57>
    DAF_Euro_6_XF: typing.ClassVar[ObjectType]  # value = <ObjectType.DAF_Euro_6_XF: 58>
    Deer: typing.ClassVar[ObjectType]  # value = <ObjectType.Deer: 59>
    Dogwood10y: typing.ClassVar[ObjectType]  # value = <ObjectType.Dogwood10y: 60>
    Dogwood20y: typing.ClassVar[ObjectType]  # value = <ObjectType.Dogwood20y: 61>
    Dumpster_2300L: typing.ClassVar[ObjectType]  # value = <ObjectType.Dumpster_2300L: 62>
    DutchChurch: typing.ClassVar[ObjectType]  # value = <ObjectType.DutchChurch: 63>
    Empty_Light_Node: typing.ClassVar[ObjectType]  # value = <ObjectType.Empty_Light_Node: 64>
    Existing: typing.ClassVar[ObjectType]  # value = <ObjectType.Existing: 65>
    FAW_Jiefang_J6M: typing.ClassVar[ObjectType]  # value = <ObjectType.FAW_Jiefang_J6M: 66>
    FShape150cm: typing.ClassVar[ObjectType]  # value = <ObjectType.FShape150cm: 67>
    FShape250cm: typing.ClassVar[ObjectType]  # value = <ObjectType.FShape250cm: 68>
    FShape350cm: typing.ClassVar[ObjectType]  # value = <ObjectType.FShape350cm: 69>
    Factory: typing.ClassVar[ObjectType]  # value = <ObjectType.Factory: 272>
    Female_Bending: typing.ClassVar[ObjectType]  # value = <ObjectType.Female_Bending: 70>
    Female_Leaning: typing.ClassVar[ObjectType]  # value = <ObjectType.Female_Leaning: 71>
    Female_Overweight: typing.ClassVar[ObjectType]  # value = <ObjectType.Female_Overweight: 72>
    Female_Regular: typing.ClassVar[ObjectType]  # value = <ObjectType.Female_Regular: 73>
    Female_wBuggy: typing.ClassVar[ObjectType]  # value = <ObjectType.Female_wBuggy: 74>
    Female_wLongCoat: typing.ClassVar[ObjectType]  # value = <ObjectType.Female_wLongCoat: 75>
    Female_wRaincoat: typing.ClassVar[ObjectType]  # value = <ObjectType.Female_wRaincoat: 76>
    Female_wShoppingCart: typing.ClassVar[ObjectType]  # value = <ObjectType.Female_wShoppingCart: 77>
    Fence: typing.ClassVar[ObjectType]  # value = <ObjectType.Fence: 275>
    Fiat_Bravo_Hatchback: typing.ClassVar[ObjectType]  # value = <ObjectType.Fiat_Bravo_Hatchback: 78>
    FireBrigade: typing.ClassVar[ObjectType]  # value = <ObjectType.FireBrigade: 79>
    Ford_Fiesta_Hatchback: typing.ClassVar[ObjectType]  # value = <ObjectType.Ford_Fiesta_Hatchback: 80>
    Ford_Focus_Stationwagon: typing.ClassVar[ObjectType]  # value = <ObjectType.Ford_Focus_Stationwagon: 81>
    Full_Trailer: typing.ClassVar[ObjectType]  # value = <ObjectType.Full_Trailer: 82>
    Garage_Ground_Floor: typing.ClassVar[ObjectType]  # value = <ObjectType.Garage_Ground_Floor: 83>
    Garage_Mid_Floor: typing.ClassVar[ObjectType]  # value = <ObjectType.Garage_Mid_Floor: 84>
    Garage_Top_Floor: typing.ClassVar[ObjectType]  # value = <ObjectType.Garage_Top_Floor: 85>
    GasStation: typing.ClassVar[ObjectType]  # value = <ObjectType.GasStation: 86>
    Genesis_GV80: typing.ClassVar[ObjectType]  # value = <ObjectType.Genesis_GV80: 87>
    Guardrail: typing.ClassVar[ObjectType]  # value = <ObjectType.Guardrail: 274>
    GuardrailReflector_RectR: typing.ClassVar[ObjectType]  # value = <ObjectType.GuardrailReflector_RectR: 88>
    GuardrailReflector_RectW: typing.ClassVar[ObjectType]  # value = <ObjectType.GuardrailReflector_RectW: 89>
    GuardrailReflector_RectWR: typing.ClassVar[ObjectType]  # value = <ObjectType.GuardrailReflector_RectWR: 90>
    GuardrailReflector_RoundR: typing.ClassVar[ObjectType]  # value = <ObjectType.GuardrailReflector_RoundR: 91>
    GuardrailReflector_RoundW: typing.ClassVar[ObjectType]  # value = <ObjectType.GuardrailReflector_RoundW: 92>
    GuardrailReflector_RoundWR: typing.ClassVar[ObjectType]  # value = <ObjectType.GuardrailReflector_RoundWR: 93>
    GuardrailReflector_RoundY: typing.ClassVar[ObjectType]  # value = <ObjectType.GuardrailReflector_RoundY: 94>
    GuidedSoftTarget: typing.ClassVar[ObjectType]  # value = <ObjectType.GuidedSoftTarget: 95>
    HOWO_T5G_Cement_Truck: typing.ClassVar[ObjectType]  # value = <ObjectType.HOWO_T5G_Cement_Truck: 96>
    Hino_Blue_Ribbon: typing.ClassVar[ObjectType]  # value = <ObjectType.Hino_Blue_Ribbon: 97>
    Honda_Pan_European_Motorcycle: typing.ClassVar[ObjectType]  # value = <ObjectType.Honda_Pan_European_Motorcycle: 98>
    Honda_Pan_European_Motorcycle_With_Driver: typing.ClassVar[
        ObjectType
    ]  # value = <ObjectType.Honda_Pan_European_Motorcycle_With_Driver: 99>
    House: typing.ClassVar[ObjectType]  # value = <ObjectType.House: 279>
    HouseModern: typing.ClassVar[ObjectType]  # value = <ObjectType.HouseModern: 100>
    HouseOld1: typing.ClassVar[ObjectType]  # value = <ObjectType.HouseOld1: 101>
    HouseOld2: typing.ClassVar[ObjectType]  # value = <ObjectType.HouseOld2: 102>
    HouseOld3: typing.ClassVar[ObjectType]  # value = <ObjectType.HouseOld3: 103>
    HouseOld4: typing.ClassVar[ObjectType]  # value = <ObjectType.HouseOld4: 104>
    HouseOld5: typing.ClassVar[ObjectType]  # value = <ObjectType.HouseOld5: 105>
    HouseOld6: typing.ClassVar[ObjectType]  # value = <ObjectType.HouseOld6: 106>
    Houses1930s: typing.ClassVar[ObjectType]  # value = <ObjectType.Houses1930s: 107>
    Hyundai_Ioniq5: typing.ClassVar[ObjectType]  # value = <ObjectType.Hyundai_Ioniq5: 108>
    Hyundai_i30_NLine: typing.ClassVar[ObjectType]  # value = <ObjectType.Hyundai_i30_NLine: 109>
    Isuzu_DMax: typing.ClassVar[ObjectType]  # value = <ObjectType.Isuzu_DMax: 110>
    Isuzu_Giga_Fire_Truck: typing.ClassVar[ObjectType]  # value = <ObjectType.Isuzu_Giga_Fire_Truck: 111>
    JAC_HFC_Series: typing.ClassVar[ObjectType]  # value = <ObjectType.JAC_HFC_Series: 112>
    JapaneseMaple10y: typing.ClassVar[ObjectType]  # value = <ObjectType.JapaneseMaple10y: 113>
    JapaneseMaple20y: typing.ClassVar[ObjectType]  # value = <ObjectType.JapaneseMaple20y: 114>
    Joby_Aviation_S4: typing.ClassVar[ObjectType]  # value = <ObjectType.Joby_Aviation_S4: 115>
    Kia_EV6: typing.ClassVar[ObjectType]  # value = <ObjectType.Kia_EV6: 116>
    Kia_EV6_wRoofRack: typing.ClassVar[ObjectType]  # value = <ObjectType.Kia_EV6_wRoofRack: 117>
    Kia_EV6_wRoofRack_Siemens: typing.ClassVar[ObjectType]  # value = <ObjectType.Kia_EV6_wRoofRack_Siemens: 118>
    Lexus_GS_450h_F_Sport_Sedan: typing.ClassVar[ObjectType]  # value = <ObjectType.Lexus_GS_450h_F_Sport_Sedan: 119>
    Lexus_LS_600h_F_Sport: typing.ClassVar[ObjectType]  # value = <ObjectType.Lexus_LS_600h_F_Sport: 120>
    LightPost: typing.ClassVar[ObjectType]  # value = <ObjectType.LightPost: 121>
    Lilac10y: typing.ClassVar[ObjectType]  # value = <ObjectType.Lilac10y: 122>
    Lilac20y: typing.ClassVar[ObjectType]  # value = <ObjectType.Lilac20y: 123>
    LinePlacedRoadImperfection: typing.ClassVar[ObjectType]  # value = <ObjectType.LinePlacedRoadImperfection: 276>
    Magnolia10y: typing.ClassVar[ObjectType]  # value = <ObjectType.Magnolia10y: 124>
    Magnolia20y: typing.ClassVar[ObjectType]  # value = <ObjectType.Magnolia20y: 125>
    Male_200: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_200: 126>
    Male_African: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_African: 127>
    Male_Bending: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_Bending: 128>
    Male_BendingOver: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_BendingOver: 129>
    Male_CyclingCyclist: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_CyclingCyclist: 130>
    Male_Female_HandInHand: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_Female_HandInHand: 131>
    Male_LargeShoulderSuitcase: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_LargeShoulderSuitcase: 132>
    Male_Leaning: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_Leaning: 133>
    Male_LeaningBack: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_LeaningBack: 134>
    Male_LyingDown: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_LyingDown: 135>
    Male_Old_White_WithStick: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_Old_White_WithStick: 136>
    Male_Old_White_WithWalker: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_Old_White_WithWalker: 137>
    Male_Old_White_WithWalkerWithWheels: typing.ClassVar[
        ObjectType
    ]  # value = <ObjectType.Male_Old_White_WithWalkerWithWheels: 138>
    Male_Overweight: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_Overweight: 139>
    Male_Regular: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_Regular: 140>
    Male_ShoppingBag: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_ShoppingBag: 141>
    Male_Sitting: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_Sitting: 142>
    Male_wBackpack: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_wBackpack: 143>
    Male_wBicycle: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_wBicycle: 144>
    Male_wLargeBackpack: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_wLargeBackpack: 145>
    Male_wLongCoat: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_wLongCoat: 146>
    Male_wRaincoat: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_wRaincoat: 147>
    Male_wSuit: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_wSuit: 148>
    Male_wSuitcase: typing.ClassVar[ObjectType]  # value = <ObjectType.Male_wSuitcase: 149>
    Man_250: typing.ClassVar[ObjectType]  # value = <ObjectType.Man_250: 150>
    Man_Asian: typing.ClassVar[ObjectType]  # value = <ObjectType.Man_Asian: 151>
    Mazda_RX8_Coupe: typing.ClassVar[ObjectType]  # value = <ObjectType.Mazda_RX8_Coupe: 152>
    MercedesBenz_Actros_1851_LS_4x2: typing.ClassVar[
        ObjectType
    ]  # value = <ObjectType.MercedesBenz_Actros_1851_LS_4x2: 153>
    MercedesBenz_Actros_1860_LS_4x2: typing.ClassVar[
        ObjectType
    ]  # value = <ObjectType.MercedesBenz_Actros_1860_LS_4x2: 154>
    MercedesBenz_Actros_2541_L_6x2: typing.ClassVar[
        ObjectType
    ]  # value = <ObjectType.MercedesBenz_Actros_2541_L_6x2: 155>
    Mitsubishi_Outlander_PHEV: typing.ClassVar[ObjectType]  # value = <ObjectType.Mitsubishi_Outlander_PHEV: 156>
    Monument: typing.ClassVar[ObjectType]  # value = <ObjectType.Monument: 157>
    NCAP_Adult: typing.ClassVar[ObjectType]  # value = <ObjectType.NCAP_Adult: 158>
    NCAP_Child: typing.ClassVar[ObjectType]  # value = <ObjectType.NCAP_Child: 159>
    NCAP_Cyclist: typing.ClassVar[ObjectType]  # value = <ObjectType.NCAP_Cyclist: 160>
    NCAP_EBTA: typing.ClassVar[ObjectType]  # value = <ObjectType.NCAP_EBTA: 161>
    NCAP_GVT: typing.ClassVar[ObjectType]  # value = <ObjectType.NCAP_GVT: 162>
    NCAP_Motorcycle: typing.ClassVar[ObjectType]  # value = <ObjectType.NCAP_Motorcycle: 163>
    NCAP_Scooter: typing.ClassVar[ObjectType]  # value = <ObjectType.NCAP_Scooter: 164>
    NCAP_StreetLight: typing.ClassVar[ObjectType]  # value = <ObjectType.NCAP_StreetLight: 165>
    NL_Ambulance_Volvo_XC60: typing.ClassVar[ObjectType]  # value = <ObjectType.NL_Ambulance_Volvo_XC60: 166>
    Nissan_Ariya: typing.ClassVar[ObjectType]  # value = <ObjectType.Nissan_Ariya: 167>
    Nissan_Cabstar_Boxtruck: typing.ClassVar[ObjectType]  # value = <ObjectType.Nissan_Cabstar_Boxtruck: 168>
    Office: typing.ClassVar[ObjectType]  # value = <ObjectType.Office: 280>
    OfficeBrownFlat: typing.ClassVar[ObjectType]  # value = <ObjectType.OfficeBrownFlat: 169>
    OfficeBrownTall1: typing.ClassVar[ObjectType]  # value = <ObjectType.OfficeBrownTall1: 170>
    OfficeBrownTall2: typing.ClassVar[ObjectType]  # value = <ObjectType.OfficeBrownTall2: 171>
    OfficeGreenTall: typing.ClassVar[ObjectType]  # value = <ObjectType.OfficeGreenTall: 172>
    Overhang1Light_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang1Light_JP: 173>
    Overhang1Light_KR: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang1Light_KR: 174>
    Overhang1Light_NL: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang1Light_NL: 175>
    Overhang1Light_US: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang1Light_US: 176>
    Overhang1Post_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang1Post_JP: 177>
    Overhang1Post_KR: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang1Post_KR: 178>
    Overhang1Post_NL: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang1Post_NL: 179>
    Overhang1Post_US: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang1Post_US: 180>
    Overhang2Lights_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang2Lights_JP: 181>
    Overhang2Lights_KR: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang2Lights_KR: 182>
    Overhang2Lights_NL: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang2Lights_NL: 183>
    Overhang2Lights_US: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang2Lights_US: 184>
    Overhang2Post_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang2Post_JP: 185>
    Overhang2Post_KR: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang2Post_KR: 186>
    Overhang2Post_NL: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang2Post_NL: 187>
    Overhang2Post_US: typing.ClassVar[ObjectType]  # value = <ObjectType.Overhang2Post_US: 188>
    OverhangDH2Lights_US: typing.ClassVar[ObjectType]  # value = <ObjectType.OverhangDH2Lights_US: 189>
    OverhangDHPost_US: typing.ClassVar[ObjectType]  # value = <ObjectType.OverhangDHPost_US: 190>
    Pallet: typing.ClassVar[ObjectType]  # value = <ObjectType.Pallet: 191>
    PedestrianSignal_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.PedestrianSignal_JP: 192>
    Peterbilt_579: typing.ClassVar[ObjectType]  # value = <ObjectType.Peterbilt_579: 193>
    Peterbilt_579_Trailer: typing.ClassVar[ObjectType]  # value = <ObjectType.Peterbilt_579_Trailer: 194>
    PlasticBarrier100cm: typing.ClassVar[ObjectType]  # value = <ObjectType.PlasticBarrier100cm: 195>
    PrismSignV_30_50_70: typing.ClassVar[ObjectType]  # value = <ObjectType.PrismSignV_30_50_70: 196>
    PrismSignV_5_10_15: typing.ClassVar[ObjectType]  # value = <ObjectType.PrismSignV_5_10_15: 197>
    PrismSignV_80_100_110: typing.ClassVar[ObjectType]  # value = <ObjectType.PrismSignV_80_100_110: 198>
    PrismSign_30_50_70: typing.ClassVar[ObjectType]  # value = <ObjectType.PrismSign_30_50_70: 199>
    PrismSign_5_10_15: typing.ClassVar[ObjectType]  # value = <ObjectType.PrismSign_5_10_15: 200>
    PrismSign_80_100_110: typing.ClassVar[ObjectType]  # value = <ObjectType.PrismSign_80_100_110: 201>
    Pylon_01: typing.ClassVar[ObjectType]  # value = <ObjectType.Pylon_01: 202>
    Pylon_02: typing.ClassVar[ObjectType]  # value = <ObjectType.Pylon_02: 203>
    ReflectorSign: typing.ClassVar[ObjectType]  # value = <ObjectType.ReflectorSign: 204>
    ReflectorSignSimple: typing.ClassVar[ObjectType]  # value = <ObjectType.ReflectorSignSimple: 205>
    Rivian_R1T: typing.ClassVar[ObjectType]  # value = <ObjectType.Rivian_R1T: 206>
    Rivian_R1T_wCover: typing.ClassVar[ObjectType]  # value = <ObjectType.Rivian_R1T_wCover: 207>
    RoadClosed_wLights: typing.ClassVar[ObjectType]  # value = <ObjectType.RoadClosed_wLights: 208>
    RoadsideLight_NL: typing.ClassVar[ObjectType]  # value = <ObjectType.RoadsideLight_NL: 209>
    RoadsideMarker: typing.ClassVar[ObjectType]  # value = <ObjectType.RoadsideMarker: 210>
    RoadsidePost: typing.ClassVar[ObjectType]  # value = <ObjectType.RoadsidePost: 211>
    RoadsidePost_NL: typing.ClassVar[ObjectType]  # value = <ObjectType.RoadsidePost_NL: 212>
    Roewe_550_S_Sedan: typing.ClassVar[ObjectType]  # value = <ObjectType.Roewe_550_S_Sedan: 213>
    Row_Crop_Tractor: typing.ClassVar[ObjectType]  # value = <ObjectType.Row_Crop_Tractor: 214>
    School: typing.ClassVar[ObjectType]  # value = <ObjectType.School: 215>
    Scooter: typing.ClassVar[ObjectType]  # value = <ObjectType.Scooter: 216>
    Scooter_wBox: typing.ClassVar[ObjectType]  # value = <ObjectType.Scooter_wBox: 217>
    Serviceberry10y: typing.ClassVar[ObjectType]  # value = <ObjectType.Serviceberry10y: 218>
    Serviceberry15y: typing.ClassVar[ObjectType]  # value = <ObjectType.Serviceberry15y: 219>
    Serviceberry5y: typing.ClassVar[ObjectType]  # value = <ObjectType.Serviceberry5y: 220>
    ShoppingCart: typing.ClassVar[ObjectType]  # value = <ObjectType.ShoppingCart: 221>
    Siemens_eRod: typing.ClassVar[ObjectType]  # value = <ObjectType.Siemens_eRod: 222>
    SignalCasing20cm_NL: typing.ClassVar[ObjectType]  # value = <ObjectType.SignalCasing20cm_NL: 223>
    SignalCasing30cmDH_US: typing.ClassVar[ObjectType]  # value = <ObjectType.SignalCasing30cmDH_US: 224>
    SignalCasing30cm_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.SignalCasing30cm_JP: 225>
    SignalCasing30cm_NL: typing.ClassVar[ObjectType]  # value = <ObjectType.SignalCasing30cm_NL: 226>
    SignalCasing30cm_US: typing.ClassVar[ObjectType]  # value = <ObjectType.SignalCasing30cm_US: 227>
    SignalCasing3_30cm_KR: typing.ClassVar[ObjectType]  # value = <ObjectType.SignalCasing3_30cm_KR: 228>
    SignalCasing4_30cm_KR: typing.ClassVar[ObjectType]  # value = <ObjectType.SignalCasing4_30cm_KR: 229>
    Skywell: typing.ClassVar[ObjectType]  # value = <ObjectType.Skywell: 230>
    SoundAbsorbingWall: typing.ClassVar[ObjectType]  # value = <ObjectType.SoundAbsorbingWall: 277>
    SpeedBump250cm: typing.ClassVar[ObjectType]  # value = <ObjectType.SpeedBump250cm: 231>
    SpeedBump350cm: typing.ClassVar[ObjectType]  # value = <ObjectType.SpeedBump350cm: 232>
    Sphere: typing.ClassVar[ObjectType]  # value = <ObjectType.Sphere: 285>
    Sports_Bike: typing.ClassVar[ObjectType]  # value = <ObjectType.Sports_Bike: 233>
    Sports_Bike_wDriver: typing.ClassVar[ObjectType]  # value = <ObjectType.Sports_Bike_wDriver: 234>
    SpringPost46cm: typing.ClassVar[ObjectType]  # value = <ObjectType.SpringPost46cm: 235>
    SpringPost75cm: typing.ClassVar[ObjectType]  # value = <ObjectType.SpringPost75cm: 236>
    SpringPost95cm: typing.ClassVar[ObjectType]  # value = <ObjectType.SpringPost95cm: 237>
    Suzuki_Hustler_Hybrid: typing.ClassVar[ObjectType]  # value = <ObjectType.Suzuki_Hustler_Hybrid: 238>
    TerracedHouses: typing.ClassVar[ObjectType]  # value = <ObjectType.TerracedHouses: 239>
    Tesla_Model_3: typing.ClassVar[ObjectType]  # value = <ObjectType.Tesla_Model_3: 240>
    Tire_Horizontal: typing.ClassVar[ObjectType]  # value = <ObjectType.Tire_Horizontal: 241>
    Tire_Vertical: typing.ClassVar[ObjectType]  # value = <ObjectType.Tire_Vertical: 242>
    Toddler_050: typing.ClassVar[ObjectType]  # value = <ObjectType.Toddler_050: 243>
    Toyota_Previa_MPV: typing.ClassVar[ObjectType]  # value = <ObjectType.Toyota_Previa_MPV: 244>
    Toyota_Prius_Sedan: typing.ClassVar[ObjectType]  # value = <ObjectType.Toyota_Prius_Sedan: 245>
    Toyota_Yaris_Hatchback: typing.ClassVar[ObjectType]  # value = <ObjectType.Toyota_Yaris_Hatchback: 246>
    TrafficSignPole: typing.ClassVar[ObjectType]  # value = <ObjectType.TrafficSignPole: 287>
    TrashBin_240L: typing.ClassVar[ObjectType]  # value = <ObjectType.TrashBin_240L: 247>
    TrashCan_Rnd_130L: typing.ClassVar[ObjectType]  # value = <ObjectType.TrashCan_Rnd_130L: 248>
    TrashCan_Sqr_160L: typing.ClassVar[ObjectType]  # value = <ObjectType.TrashCan_Sqr_160L: 249>
    TriangleParkingSpaceLock: typing.ClassVar[ObjectType]  # value = <ObjectType.TriangleParkingSpaceLock: 250>
    Tripod: typing.ClassVar[ObjectType]  # value = <ObjectType.Tripod: 286>
    TurkishHazel10y: typing.ClassVar[ObjectType]  # value = <ObjectType.TurkishHazel10y: 251>
    TurkishHazel20y: typing.ClassVar[ObjectType]  # value = <ObjectType.TurkishHazel20y: 252>
    US_Police_Volvo_XC60: typing.ClassVar[ObjectType]  # value = <ObjectType.US_Police_Volvo_XC60: 253>
    VehicleSignal30cm_FL_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.VehicleSignal30cm_FL_JP: 254>
    VehicleSignal30cm_FR_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.VehicleSignal30cm_FR_JP: 255>
    VehicleSignal30cm_F_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.VehicleSignal30cm_F_JP: 256>
    VehicleSignal30cm_L_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.VehicleSignal30cm_L_JP: 257>
    VehicleSignal30cm_R_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.VehicleSignal30cm_R_JP: 258>
    VehicleSignalGreen30cm_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.VehicleSignalGreen30cm_JP: 259>
    VehicleSignalOrange30cm_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.VehicleSignalOrange30cm_JP: 260>
    VehicleSignalRed30cm_JP: typing.ClassVar[ObjectType]  # value = <ObjectType.VehicleSignalRed30cm_JP: 261>
    Volvo_FH16: typing.ClassVar[ObjectType]  # value = <ObjectType.Volvo_FH16: 262>
    Volvo_XC60: typing.ClassVar[ObjectType]  # value = <ObjectType.Volvo_XC60: 263>
    Wall: typing.ClassVar[ObjectType]  # value = <ObjectType.Wall: 278>
    Warehouse: typing.ClassVar[ObjectType]  # value = <ObjectType.Warehouse: 264>
    Wheat_A: typing.ClassVar[ObjectType]  # value = <ObjectType.Wheat_A: 265>
    Wheat_B: typing.ClassVar[ObjectType]  # value = <ObjectType.Wheat_B: 266>
    Wheat_C: typing.ClassVar[ObjectType]  # value = <ObjectType.Wheat_C: 267>
    WheelieBin_1100L: typing.ClassVar[ObjectType]  # value = <ObjectType.WheelieBin_1100L: 268>
    Windmill: typing.ClassVar[ObjectType]  # value = <ObjectType.Windmill: 269>
    Wuling_Hongguang: typing.ClassVar[ObjectType]  # value = <ObjectType.Wuling_Hongguang: 270>
    __members__: typing.ClassVar[
        dict[str, ObjectType]
    ]  # value = {'ADAC_target_yellow_merc': <ObjectType.ADAC_target_yellow_merc: 0>, 'ApartmentBuilding': <ObjectType.ApartmentBuilding: 1>, 'ArrowBoard_Trailer': <ObjectType.ArrowBoard_Trailer: 2>, 'Ash10y': <ObjectType.Ash10y: 3>, 'Ash20y': <ObjectType.Ash20y: 4>, 'Audi_A3': <ObjectType.Audi_A3: 5>, 'Audi_A8_Sedan': <ObjectType.Audi_A8_Sedan: 6>, 'AustrianPine10y': <ObjectType.AustrianPine10y: 7>, 'AustrianPine20y': <ObjectType.AustrianPine20y: 8>, 'BE_Police_Volvo_XC60': <ObjectType.BE_Police_Volvo_XC60: 9>, 'BMW_X5_SUV': <ObjectType.BMW_X5_SUV: 10>, 'BMW_Z3_Convertible': <ObjectType.BMW_Z3_Convertible: 11>, 'BalloonCar': <ObjectType.BalloonCar: 12>, 'BarrierFence': <ObjectType.BarrierFence: 13>, 'Birch10y': <ObjectType.Birch10y: 14>, 'Birch20y': <ObjectType.Birch20y: 15>, 'BlueSpruce10y': <ObjectType.BlueSpruce10y: 16>, 'BlueSpruce20y': <ObjectType.BlueSpruce20y: 17>, 'BottsDots_White': <ObjectType.BottsDots_White: 18>, 'BottsDots_Yellow': <ObjectType.BottsDots_Yellow: 19>, 'Boy_100': <ObjectType.Boy_100: 20>, 'Boy_150': <ObjectType.Boy_150: 21>, 'Building_00A': <ObjectType.Building_00A: 22>, 'Building_01A': <ObjectType.Building_01A: 23>, 'Building_02A': <ObjectType.Building_02A: 24>, 'Building_03A': <ObjectType.Building_03A: 25>, 'Building_04A': <ObjectType.Building_04A: 26>, 'Building_05A': <ObjectType.Building_05A: 27>, 'Building_06A': <ObjectType.Building_06A: 28>, 'Building_07A': <ObjectType.Building_07A: 29>, 'Building_08A': <ObjectType.Building_08A: 30>, 'Busstop': <ObjectType.Busstop: 31>, 'CAT_725': <ObjectType.CAT_725: 32>, 'Cadillac_Escalade': <ObjectType.Cadillac_Escalade: 33>, 'CarDealer': <ObjectType.CarDealer: 34>, 'Car_Trailer_Small': <ObjectType.Car_Trailer_Small: 35>, 'CatsEyesR': <ObjectType.CatsEyesR: 36>, 'CatsEyesW': <ObjectType.CatsEyesW: 37>, 'CatsEyesWR': <ObjectType.CatsEyesWR: 38>, 'CatsEyesWY': <ObjectType.CatsEyesWY: 39>, 'CatsEyesY': <ObjectType.CatsEyesY: 40>, 'Child_Leaning': <ObjectType.Child_Leaning: 41>, 'Child_Overweight': <ObjectType.Child_Overweight: 42>, 'Child_Regular': <ObjectType.Child_Regular: 43>, 'Child_Sitting': <ObjectType.Child_Sitting: 44>, 'CinderBlock_A': <ObjectType.CinderBlock_A: 45>, 'CinderBlock_B': <ObjectType.CinderBlock_B: 46>, 'CinderBlock_C': <ObjectType.CinderBlock_C: 47>, 'Citroen_C3_Hatchback': <ObjectType.Citroen_C3_Hatchback: 48>, 'ConstructionSign_JP': <ObjectType.ConstructionSign_JP: 49>, 'Container_Trailer': <ObjectType.Container_Trailer: 50>, 'CornerReflector138mm': <ObjectType.CornerReflector138mm: 51>, 'CornerReflector176_8mm': <ObjectType.CornerReflector176_8mm: 52>, 'CornerReflector46_35mm': <ObjectType.CornerReflector46_35mm: 53>, 'Cotton_A': <ObjectType.Cotton_A: 54>, 'Cotton_B': <ObjectType.Cotton_B: 55>, 'Cotton_C': <ObjectType.Cotton_C: 56>, 'DAF_95_XF': <ObjectType.DAF_95_XF: 57>, 'DAF_Euro_6_XF': <ObjectType.DAF_Euro_6_XF: 58>, 'Deer': <ObjectType.Deer: 59>, 'Dogwood10y': <ObjectType.Dogwood10y: 60>, 'Dogwood20y': <ObjectType.Dogwood20y: 61>, 'Dumpster_2300L': <ObjectType.Dumpster_2300L: 62>, 'DutchChurch': <ObjectType.DutchChurch: 63>, 'Empty_Light_Node': <ObjectType.Empty_Light_Node: 64>, 'Existing': <ObjectType.Existing: 65>, 'FAW_Jiefang_J6M': <ObjectType.FAW_Jiefang_J6M: 66>, 'FShape150cm': <ObjectType.FShape150cm: 67>, 'FShape250cm': <ObjectType.FShape250cm: 68>, 'FShape350cm': <ObjectType.FShape350cm: 69>, 'Female_Bending': <ObjectType.Female_Bending: 70>, 'Female_Leaning': <ObjectType.Female_Leaning: 71>, 'Female_Overweight': <ObjectType.Female_Overweight: 72>, 'Female_Regular': <ObjectType.Female_Regular: 73>, 'Female_wBuggy': <ObjectType.Female_wBuggy: 74>, 'Female_wLongCoat': <ObjectType.Female_wLongCoat: 75>, 'Female_wRaincoat': <ObjectType.Female_wRaincoat: 76>, 'Female_wShoppingCart': <ObjectType.Female_wShoppingCart: 77>, 'Fiat_Bravo_Hatchback': <ObjectType.Fiat_Bravo_Hatchback: 78>, 'FireBrigade': <ObjectType.FireBrigade: 79>, 'Ford_Fiesta_Hatchback': <ObjectType.Ford_Fiesta_Hatchback: 80>, 'Ford_Focus_Stationwagon': <ObjectType.Ford_Focus_Stationwagon: 81>, 'Full_Trailer': <ObjectType.Full_Trailer: 82>, 'Garage_Ground_Floor': <ObjectType.Garage_Ground_Floor: 83>, 'Garage_Mid_Floor': <ObjectType.Garage_Mid_Floor: 84>, 'Garage_Top_Floor': <ObjectType.Garage_Top_Floor: 85>, 'GasStation': <ObjectType.GasStation: 86>, 'Genesis_GV80': <ObjectType.Genesis_GV80: 87>, 'GuardrailReflector_RectR': <ObjectType.GuardrailReflector_RectR: 88>, 'GuardrailReflector_RectW': <ObjectType.GuardrailReflector_RectW: 89>, 'GuardrailReflector_RectWR': <ObjectType.GuardrailReflector_RectWR: 90>, 'GuardrailReflector_RoundR': <ObjectType.GuardrailReflector_RoundR: 91>, 'GuardrailReflector_RoundW': <ObjectType.GuardrailReflector_RoundW: 92>, 'GuardrailReflector_RoundWR': <ObjectType.GuardrailReflector_RoundWR: 93>, 'GuardrailReflector_RoundY': <ObjectType.GuardrailReflector_RoundY: 94>, 'GuidedSoftTarget': <ObjectType.GuidedSoftTarget: 95>, 'HOWO_T5G_Cement_Truck': <ObjectType.HOWO_T5G_Cement_Truck: 96>, 'Hino_Blue_Ribbon': <ObjectType.Hino_Blue_Ribbon: 97>, 'Honda_Pan_European_Motorcycle': <ObjectType.Honda_Pan_European_Motorcycle: 98>, 'Honda_Pan_European_Motorcycle_With_Driver': <ObjectType.Honda_Pan_European_Motorcycle_With_Driver: 99>, 'HouseModern': <ObjectType.HouseModern: 100>, 'HouseOld1': <ObjectType.HouseOld1: 101>, 'HouseOld2': <ObjectType.HouseOld2: 102>, 'HouseOld3': <ObjectType.HouseOld3: 103>, 'HouseOld4': <ObjectType.HouseOld4: 104>, 'HouseOld5': <ObjectType.HouseOld5: 105>, 'HouseOld6': <ObjectType.HouseOld6: 106>, 'Houses1930s': <ObjectType.Houses1930s: 107>, 'Hyundai_Ioniq5': <ObjectType.Hyundai_Ioniq5: 108>, 'Hyundai_i30_NLine': <ObjectType.Hyundai_i30_NLine: 109>, 'Isuzu_DMax': <ObjectType.Isuzu_DMax: 110>, 'Isuzu_Giga_Fire_Truck': <ObjectType.Isuzu_Giga_Fire_Truck: 111>, 'JAC_HFC_Series': <ObjectType.JAC_HFC_Series: 112>, 'JapaneseMaple10y': <ObjectType.JapaneseMaple10y: 113>, 'JapaneseMaple20y': <ObjectType.JapaneseMaple20y: 114>, 'Joby_Aviation_S4': <ObjectType.Joby_Aviation_S4: 115>, 'Kia_EV6': <ObjectType.Kia_EV6: 116>, 'Kia_EV6_wRoofRack': <ObjectType.Kia_EV6_wRoofRack: 117>, 'Kia_EV6_wRoofRack_Siemens': <ObjectType.Kia_EV6_wRoofRack_Siemens: 118>, 'Lexus_GS_450h_F_Sport_Sedan': <ObjectType.Lexus_GS_450h_F_Sport_Sedan: 119>, 'Lexus_LS_600h_F_Sport': <ObjectType.Lexus_LS_600h_F_Sport: 120>, 'LightPost': <ObjectType.LightPost: 121>, 'Lilac10y': <ObjectType.Lilac10y: 122>, 'Lilac20y': <ObjectType.Lilac20y: 123>, 'Magnolia10y': <ObjectType.Magnolia10y: 124>, 'Magnolia20y': <ObjectType.Magnolia20y: 125>, 'Male_200': <ObjectType.Male_200: 126>, 'Male_African': <ObjectType.Male_African: 127>, 'Male_Bending': <ObjectType.Male_Bending: 128>, 'Male_BendingOver': <ObjectType.Male_BendingOver: 129>, 'Male_CyclingCyclist': <ObjectType.Male_CyclingCyclist: 130>, 'Male_Female_HandInHand': <ObjectType.Male_Female_HandInHand: 131>, 'Male_LargeShoulderSuitcase': <ObjectType.Male_LargeShoulderSuitcase: 132>, 'Male_Leaning': <ObjectType.Male_Leaning: 133>, 'Male_LeaningBack': <ObjectType.Male_LeaningBack: 134>, 'Male_LyingDown': <ObjectType.Male_LyingDown: 135>, 'Male_Old_White_WithStick': <ObjectType.Male_Old_White_WithStick: 136>, 'Male_Old_White_WithWalker': <ObjectType.Male_Old_White_WithWalker: 137>, 'Male_Old_White_WithWalkerWithWheels': <ObjectType.Male_Old_White_WithWalkerWithWheels: 138>, 'Male_Overweight': <ObjectType.Male_Overweight: 139>, 'Male_Regular': <ObjectType.Male_Regular: 140>, 'Male_ShoppingBag': <ObjectType.Male_ShoppingBag: 141>, 'Male_Sitting': <ObjectType.Male_Sitting: 142>, 'Male_wBackpack': <ObjectType.Male_wBackpack: 143>, 'Male_wBicycle': <ObjectType.Male_wBicycle: 144>, 'Male_wLargeBackpack': <ObjectType.Male_wLargeBackpack: 145>, 'Male_wLongCoat': <ObjectType.Male_wLongCoat: 146>, 'Male_wRaincoat': <ObjectType.Male_wRaincoat: 147>, 'Male_wSuit': <ObjectType.Male_wSuit: 148>, 'Male_wSuitcase': <ObjectType.Male_wSuitcase: 149>, 'Man_250': <ObjectType.Man_250: 150>, 'Man_Asian': <ObjectType.Man_Asian: 151>, 'Mazda_RX8_Coupe': <ObjectType.Mazda_RX8_Coupe: 152>, 'MercedesBenz_Actros_1851_LS_4x2': <ObjectType.MercedesBenz_Actros_1851_LS_4x2: 153>, 'MercedesBenz_Actros_1860_LS_4x2': <ObjectType.MercedesBenz_Actros_1860_LS_4x2: 154>, 'MercedesBenz_Actros_2541_L_6x2': <ObjectType.MercedesBenz_Actros_2541_L_6x2: 155>, 'Mitsubishi_Outlander_PHEV': <ObjectType.Mitsubishi_Outlander_PHEV: 156>, 'Monument': <ObjectType.Monument: 157>, 'NCAP_Adult': <ObjectType.NCAP_Adult: 158>, 'NCAP_Child': <ObjectType.NCAP_Child: 159>, 'NCAP_Cyclist': <ObjectType.NCAP_Cyclist: 160>, 'NCAP_EBTA': <ObjectType.NCAP_EBTA: 161>, 'NCAP_GVT': <ObjectType.NCAP_GVT: 162>, 'NCAP_Motorcycle': <ObjectType.NCAP_Motorcycle: 163>, 'NCAP_Scooter': <ObjectType.NCAP_Scooter: 164>, 'NCAP_StreetLight': <ObjectType.NCAP_StreetLight: 165>, 'NL_Ambulance_Volvo_XC60': <ObjectType.NL_Ambulance_Volvo_XC60: 166>, 'Nissan_Ariya': <ObjectType.Nissan_Ariya: 167>, 'Nissan_Cabstar_Boxtruck': <ObjectType.Nissan_Cabstar_Boxtruck: 168>, 'OfficeBrownFlat': <ObjectType.OfficeBrownFlat: 169>, 'OfficeBrownTall1': <ObjectType.OfficeBrownTall1: 170>, 'OfficeBrownTall2': <ObjectType.OfficeBrownTall2: 171>, 'OfficeGreenTall': <ObjectType.OfficeGreenTall: 172>, 'Overhang1Light_JP': <ObjectType.Overhang1Light_JP: 173>, 'Overhang1Light_KR': <ObjectType.Overhang1Light_KR: 174>, 'Overhang1Light_NL': <ObjectType.Overhang1Light_NL: 175>, 'Overhang1Light_US': <ObjectType.Overhang1Light_US: 176>, 'Overhang1Post_JP': <ObjectType.Overhang1Post_JP: 177>, 'Overhang1Post_KR': <ObjectType.Overhang1Post_KR: 178>, 'Overhang1Post_NL': <ObjectType.Overhang1Post_NL: 179>, 'Overhang1Post_US': <ObjectType.Overhang1Post_US: 180>, 'Overhang2Lights_JP': <ObjectType.Overhang2Lights_JP: 181>, 'Overhang2Lights_KR': <ObjectType.Overhang2Lights_KR: 182>, 'Overhang2Lights_NL': <ObjectType.Overhang2Lights_NL: 183>, 'Overhang2Lights_US': <ObjectType.Overhang2Lights_US: 184>, 'Overhang2Post_JP': <ObjectType.Overhang2Post_JP: 185>, 'Overhang2Post_KR': <ObjectType.Overhang2Post_KR: 186>, 'Overhang2Post_NL': <ObjectType.Overhang2Post_NL: 187>, 'Overhang2Post_US': <ObjectType.Overhang2Post_US: 188>, 'OverhangDH2Lights_US': <ObjectType.OverhangDH2Lights_US: 189>, 'OverhangDHPost_US': <ObjectType.OverhangDHPost_US: 190>, 'Pallet': <ObjectType.Pallet: 191>, 'PedestrianSignal_JP': <ObjectType.PedestrianSignal_JP: 192>, 'Peterbilt_579': <ObjectType.Peterbilt_579: 193>, 'Peterbilt_579_Trailer': <ObjectType.Peterbilt_579_Trailer: 194>, 'PlasticBarrier100cm': <ObjectType.PlasticBarrier100cm: 195>, 'PrismSignV_30_50_70': <ObjectType.PrismSignV_30_50_70: 196>, 'PrismSignV_5_10_15': <ObjectType.PrismSignV_5_10_15: 197>, 'PrismSignV_80_100_110': <ObjectType.PrismSignV_80_100_110: 198>, 'PrismSign_30_50_70': <ObjectType.PrismSign_30_50_70: 199>, 'PrismSign_5_10_15': <ObjectType.PrismSign_5_10_15: 200>, 'PrismSign_80_100_110': <ObjectType.PrismSign_80_100_110: 201>, 'Pylon_01': <ObjectType.Pylon_01: 202>, 'Pylon_02': <ObjectType.Pylon_02: 203>, 'ReflectorSign': <ObjectType.ReflectorSign: 204>, 'ReflectorSignSimple': <ObjectType.ReflectorSignSimple: 205>, 'Rivian_R1T': <ObjectType.Rivian_R1T: 206>, 'Rivian_R1T_wCover': <ObjectType.Rivian_R1T_wCover: 207>, 'RoadClosed_wLights': <ObjectType.RoadClosed_wLights: 208>, 'RoadsideLight_NL': <ObjectType.RoadsideLight_NL: 209>, 'RoadsideMarker': <ObjectType.RoadsideMarker: 210>, 'RoadsidePost': <ObjectType.RoadsidePost: 211>, 'RoadsidePost_NL': <ObjectType.RoadsidePost_NL: 212>, 'Roewe_550_S_Sedan': <ObjectType.Roewe_550_S_Sedan: 213>, 'Row_Crop_Tractor': <ObjectType.Row_Crop_Tractor: 214>, 'School': <ObjectType.School: 215>, 'Scooter': <ObjectType.Scooter: 216>, 'Scooter_wBox': <ObjectType.Scooter_wBox: 217>, 'Serviceberry10y': <ObjectType.Serviceberry10y: 218>, 'Serviceberry15y': <ObjectType.Serviceberry15y: 219>, 'Serviceberry5y': <ObjectType.Serviceberry5y: 220>, 'ShoppingCart': <ObjectType.ShoppingCart: 221>, 'Siemens_eRod': <ObjectType.Siemens_eRod: 222>, 'SignalCasing20cm_NL': <ObjectType.SignalCasing20cm_NL: 223>, 'SignalCasing30cmDH_US': <ObjectType.SignalCasing30cmDH_US: 224>, 'SignalCasing30cm_JP': <ObjectType.SignalCasing30cm_JP: 225>, 'SignalCasing30cm_NL': <ObjectType.SignalCasing30cm_NL: 226>, 'SignalCasing30cm_US': <ObjectType.SignalCasing30cm_US: 227>, 'SignalCasing3_30cm_KR': <ObjectType.SignalCasing3_30cm_KR: 228>, 'SignalCasing4_30cm_KR': <ObjectType.SignalCasing4_30cm_KR: 229>, 'Skywell': <ObjectType.Skywell: 230>, 'SpeedBump250cm': <ObjectType.SpeedBump250cm: 231>, 'SpeedBump350cm': <ObjectType.SpeedBump350cm: 232>, 'Sports_Bike': <ObjectType.Sports_Bike: 233>, 'Sports_Bike_wDriver': <ObjectType.Sports_Bike_wDriver: 234>, 'SpringPost46cm': <ObjectType.SpringPost46cm: 235>, 'SpringPost75cm': <ObjectType.SpringPost75cm: 236>, 'SpringPost95cm': <ObjectType.SpringPost95cm: 237>, 'Suzuki_Hustler_Hybrid': <ObjectType.Suzuki_Hustler_Hybrid: 238>, 'TerracedHouses': <ObjectType.TerracedHouses: 239>, 'Tesla_Model_3': <ObjectType.Tesla_Model_3: 240>, 'Tire_Horizontal': <ObjectType.Tire_Horizontal: 241>, 'Tire_Vertical': <ObjectType.Tire_Vertical: 242>, 'Toddler_050': <ObjectType.Toddler_050: 243>, 'Toyota_Previa_MPV': <ObjectType.Toyota_Previa_MPV: 244>, 'Toyota_Prius_Sedan': <ObjectType.Toyota_Prius_Sedan: 245>, 'Toyota_Yaris_Hatchback': <ObjectType.Toyota_Yaris_Hatchback: 246>, 'TrashBin_240L': <ObjectType.TrashBin_240L: 247>, 'TrashCan_Rnd_130L': <ObjectType.TrashCan_Rnd_130L: 248>, 'TrashCan_Sqr_160L': <ObjectType.TrashCan_Sqr_160L: 249>, 'TriangleParkingSpaceLock': <ObjectType.TriangleParkingSpaceLock: 250>, 'TurkishHazel10y': <ObjectType.TurkishHazel10y: 251>, 'TurkishHazel20y': <ObjectType.TurkishHazel20y: 252>, 'US_Police_Volvo_XC60': <ObjectType.US_Police_Volvo_XC60: 253>, 'VehicleSignal30cm_FL_JP': <ObjectType.VehicleSignal30cm_FL_JP: 254>, 'VehicleSignal30cm_FR_JP': <ObjectType.VehicleSignal30cm_FR_JP: 255>, 'VehicleSignal30cm_F_JP': <ObjectType.VehicleSignal30cm_F_JP: 256>, 'VehicleSignal30cm_L_JP': <ObjectType.VehicleSignal30cm_L_JP: 257>, 'VehicleSignal30cm_R_JP': <ObjectType.VehicleSignal30cm_R_JP: 258>, 'VehicleSignalGreen30cm_JP': <ObjectType.VehicleSignalGreen30cm_JP: 259>, 'VehicleSignalOrange30cm_JP': <ObjectType.VehicleSignalOrange30cm_JP: 260>, 'VehicleSignalRed30cm_JP': <ObjectType.VehicleSignalRed30cm_JP: 261>, 'Volvo_FH16': <ObjectType.Volvo_FH16: 262>, 'Volvo_XC60': <ObjectType.Volvo_XC60: 263>, 'Warehouse': <ObjectType.Warehouse: 264>, 'Wheat_A': <ObjectType.Wheat_A: 265>, 'Wheat_B': <ObjectType.Wheat_B: 266>, 'Wheat_C': <ObjectType.Wheat_C: 267>, 'WheelieBin_1100L': <ObjectType.WheelieBin_1100L: 268>, 'Windmill': <ObjectType.Windmill: 269>, 'Wuling_Hongguang': <ObjectType.Wuling_Hongguang: 270>, 'Church': <ObjectType.Church: 271>, 'Factory': <ObjectType.Factory: 272>, 'ConcreteGuardrail': <ObjectType.ConcreteGuardrail: 273>, 'Guardrail': <ObjectType.Guardrail: 274>, 'Fence': <ObjectType.Fence: 275>, 'LinePlacedRoadImperfection': <ObjectType.LinePlacedRoadImperfection: 276>, 'SoundAbsorbingWall': <ObjectType.SoundAbsorbingWall: 277>, 'Wall': <ObjectType.Wall: 278>, 'House': <ObjectType.House: 279>, 'Office': <ObjectType.Office: 280>, 'Box': <ObjectType.Box: 281>, 'Capsule': <ObjectType.Capsule: 282>, 'Cone': <ObjectType.Cone: 283>, 'Cylinder': <ObjectType.Cylinder: 284>, 'Sphere': <ObjectType.Sphere: 285>, 'Tripod': <ObjectType.Tripod: 286>, 'TrafficSignPole': <ObjectType.TrafficSignPole: 287>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class Orientation:
    pitch: float
    roll: float
    yaw: float
    def __array__(self) -> numpy.ndarray[numpy.float64]: ...
    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, roll: float, pitch: float, yaw: float) -> None: ...
    @typing.overload
    def __init__(self, zero_init: bool) -> None:
        """
        Initialise with zeros or with NaNs
        """

    @typing.overload
    def __init__(self, array: numpy.ndarray[numpy.float64]) -> None: ...
    def __repr__(self) -> str: ...

class ParameterRange:
    """
    Members:

      ParamPolyRangeTypeArcLength

      ParamPolyRangeTypeNormalized
    """

    ParamPolyRangeTypeArcLength: typing.ClassVar[
        ParameterRange
    ]  # value = <ParameterRange.ParamPolyRangeTypeArcLength: 0>
    ParamPolyRangeTypeNormalized: typing.ClassVar[
        ParameterRange
    ]  # value = <ParameterRange.ParamPolyRangeTypeNormalized: 1>
    __members__: typing.ClassVar[
        dict[str, ParameterRange]
    ]  # value = {'ParamPolyRangeTypeArcLength': <ParameterRange.ParamPolyRangeTypeArcLength: 0>, 'ParamPolyRangeTypeNormalized': <ParameterRange.ParamPolyRangeTypeNormalized: 1>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class Position:
    x: float
    y: float
    z: float
    def __array__(self) -> numpy.ndarray[numpy.float64]: ...
    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, x: float, y: float, z: float) -> None: ...
    @typing.overload
    def __init__(self, zero_init: bool) -> None:
        """
        Initialise with zeros or with NaNs
        """

    @typing.overload
    def __init__(self, array: numpy.ndarray[numpy.float64]) -> None: ...
    def __repr__(self) -> str: ...

class Road:
    def add_cubic_polynomial_section(self, length: float, a: float, b: float, c: float, d: float) -> Road:
        """
        Add a cubic polynomial section to the road
        """

    def add_curve_section(self, length: float, curvature: float) -> Road:
        """
        Add a curve section to the road
        """

    def add_lane(
        self,
        road_side: RoadSideType,
        width: float,
        lane_type: LaneType = ...,
        start_offset: float = 0.0,
        end_offset: float = float("inf"),
    ) -> Road:
        """
        Add a lane to the road
        """

    def add_parametric_cubic_polynomial_section(
        self,
        length: float,
        aU: float,
        bU: float,
        cU: float,
        dU: float,
        aV: float,
        bV: float,
        cV: float,
        dV: float,
        parameter_range: ParameterRange,
    ) -> Road:
        """
        Add a parametric cubic polynomial section to the road
        """

    def add_parking_space(
        self,
        length: float,
        width: float,
        yaw: float = 0,
        road_side: RoadSideType = ...,
        side_offset: float = 0,
        offset: float = 0,
    ) -> Road:
        """
        Add a parking space to the road
        """

    def add_spiral_section(self, length: float, start_curvature: float, end_curvature: float) -> Road:
        """
        Add a spiral section to the road
        """

    def add_straight_section(self, length: float) -> Road:
        """
        Add a straight section to the road
        """

    def set_asphalt_color(self, r: float, g: float, b: float) -> Road:
        """
        Set the asphalt color
        """

    def set_asphalt_texture_scale(self, texture_scale: float) -> Road:
        """
        Set the asphalt texture scale
        """

    def set_asphalt_tone(self, tone: AsphaltTone) -> Road:
        """
        Set the asphalt tone
        """

    def set_asphalt_type(self, asphalt_type: AsphaltType) -> Road:
        """
        Set the asphalt type
        """

    def set_position(self, position: Position) -> Road:
        """
        Set the position of the road
        """

    def set_speed_limit_profile(
        self, value: float, start_offset: float = 0.0, end_offset: float = float("inf")
    ) -> Road:
        """
        Set the speed limit profile
        """

    def set_traffic_side(self, traffic_side: TrafficSide) -> Road:
        """
        Set the traffic side of the road
        """

    @property
    def length(self) -> float:
        """
        Get the length of the road
        """

class RoadSideType:
    """
    Members:

      RoadSideTypeLeft

      RoadSideTypeRight
    """

    RoadSideTypeLeft: typing.ClassVar[RoadSideType]  # value = <RoadSideType.RoadSideTypeLeft: 0>
    RoadSideTypeRight: typing.ClassVar[RoadSideType]  # value = <RoadSideType.RoadSideTypeRight: 1>
    __members__: typing.ClassVar[
        dict[str, RoadSideType]
    ]  # value = {'RoadSideTypeLeft': <RoadSideType.RoadSideTypeLeft: 0>, 'RoadSideTypeRight': <RoadSideType.RoadSideTypeRight: 1>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class SensorDetectability:
    """
    Members:

      SensorDetectabilityDetectable

      SensorDetectabilityInvisible

      SensorDetectabilityOccluding
    """

    SensorDetectabilityDetectable: typing.ClassVar[
        SensorDetectability
    ]  # value = <SensorDetectability.SensorDetectabilityDetectable: 2>
    SensorDetectabilityInvisible: typing.ClassVar[
        SensorDetectability
    ]  # value = <SensorDetectability.SensorDetectabilityInvisible: 0>
    SensorDetectabilityOccluding: typing.ClassVar[
        SensorDetectability
    ]  # value = <SensorDetectability.SensorDetectabilityOccluding: 1>
    __members__: typing.ClassVar[
        dict[str, SensorDetectability]
    ]  # value = {'SensorDetectabilityDetectable': <SensorDetectability.SensorDetectabilityDetectable: 2>, 'SensorDetectabilityInvisible': <SensorDetectability.SensorDetectabilityInvisible: 0>, 'SensorDetectabilityOccluding': <SensorDetectability.SensorDetectabilityOccluding: 1>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class SensorType:
    """
    Members:

      AIR

      ALMS

      BRS

      CAMERA

      IR_BEACON

      IR_OBU

      RF_BEACON

      RF_OBU

      DEPTH_CAMERA

      ISS

      LIDA

      LMS

      OCS

      PCS

      PHYSICS_BASED_CAMERA_UNREAL

      RADAR

      TIS

      TRAFFIC_SIGNAL

      ULTRASONIC

      WORLD_VIEWER
    """

    AIR: typing.ClassVar[SensorType]  # value = <SensorType.AIR: 0>
    ALMS: typing.ClassVar[SensorType]  # value = <SensorType.ALMS: 1>
    BRS: typing.ClassVar[SensorType]  # value = <SensorType.BRS: 2>
    CAMERA: typing.ClassVar[SensorType]  # value = <SensorType.CAMERA: 3>
    DEPTH_CAMERA: typing.ClassVar[SensorType]  # value = <SensorType.DEPTH_CAMERA: 8>
    IR_BEACON: typing.ClassVar[SensorType]  # value = <SensorType.IR_BEACON: 4>
    IR_OBU: typing.ClassVar[SensorType]  # value = <SensorType.IR_OBU: 5>
    ISS: typing.ClassVar[SensorType]  # value = <SensorType.ISS: 9>
    LIDA: typing.ClassVar[SensorType]  # value = <SensorType.LIDA: 10>
    LMS: typing.ClassVar[SensorType]  # value = <SensorType.LMS: 11>
    OCS: typing.ClassVar[SensorType]  # value = <SensorType.OCS: 12>
    PCS: typing.ClassVar[SensorType]  # value = <SensorType.PCS: 13>
    PHYSICS_BASED_CAMERA_UNREAL: typing.ClassVar[SensorType]  # value = <SensorType.PHYSICS_BASED_CAMERA_UNREAL: 14>
    RADAR: typing.ClassVar[SensorType]  # value = <SensorType.RADAR: 15>
    RF_BEACON: typing.ClassVar[SensorType]  # value = <SensorType.RF_BEACON: 6>
    RF_OBU: typing.ClassVar[SensorType]  # value = <SensorType.RF_OBU: 7>
    TIS: typing.ClassVar[SensorType]  # value = <SensorType.TIS: 16>
    TRAFFIC_SIGNAL: typing.ClassVar[SensorType]  # value = <SensorType.TRAFFIC_SIGNAL: 17>
    ULTRASONIC: typing.ClassVar[SensorType]  # value = <SensorType.ULTRASONIC: 18>
    WORLD_VIEWER: typing.ClassVar[SensorType]  # value = <SensorType.WORLD_VIEWER: 19>
    __members__: typing.ClassVar[
        dict[str, SensorType]
    ]  # value = {'AIR': <SensorType.AIR: 0>, 'ALMS': <SensorType.ALMS: 1>, 'BRS': <SensorType.BRS: 2>, 'CAMERA': <SensorType.CAMERA: 3>, 'IR_BEACON': <SensorType.IR_BEACON: 4>, 'IR_OBU': <SensorType.IR_OBU: 5>, 'RF_BEACON': <SensorType.RF_BEACON: 6>, 'RF_OBU': <SensorType.RF_OBU: 7>, 'DEPTH_CAMERA': <SensorType.DEPTH_CAMERA: 8>, 'ISS': <SensorType.ISS: 9>, 'LIDA': <SensorType.LIDA: 10>, 'LMS': <SensorType.LMS: 11>, 'OCS': <SensorType.OCS: 12>, 'PCS': <SensorType.PCS: 13>, 'PHYSICS_BASED_CAMERA_UNREAL': <SensorType.PHYSICS_BASED_CAMERA_UNREAL: 14>, 'RADAR': <SensorType.RADAR: 15>, 'TIS': <SensorType.TIS: 16>, 'TRAFFIC_SIGNAL': <SensorType.TRAFFIC_SIGNAL: 17>, 'ULTRASONIC': <SensorType.ULTRASONIC: 18>, 'WORLD_VIEWER': <SensorType.WORLD_VIEWER: 19>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class SimulationSpeed:
    """
    Members:

      SimulationSpeedAsFastAsPossible

      SimulationSpeedHalfWallClockTime

      SimulationSpeedQuarterWallClockTime

      SimulationSpeedWallClockTime
    """

    SimulationSpeedAsFastAsPossible: typing.ClassVar[
        SimulationSpeed
    ]  # value = <SimulationSpeed.SimulationSpeedAsFastAsPossible: 0>
    SimulationSpeedHalfWallClockTime: typing.ClassVar[
        SimulationSpeed
    ]  # value = <SimulationSpeed.SimulationSpeedHalfWallClockTime: 2>
    SimulationSpeedQuarterWallClockTime: typing.ClassVar[
        SimulationSpeed
    ]  # value = <SimulationSpeed.SimulationSpeedQuarterWallClockTime: 3>
    SimulationSpeedWallClockTime: typing.ClassVar[
        SimulationSpeed
    ]  # value = <SimulationSpeed.SimulationSpeedWallClockTime: 1>
    __members__: typing.ClassVar[
        dict[str, SimulationSpeed]
    ]  # value = {'SimulationSpeedAsFastAsPossible': <SimulationSpeed.SimulationSpeedAsFastAsPossible: 0>, 'SimulationSpeedHalfWallClockTime': <SimulationSpeed.SimulationSpeedHalfWallClockTime: 2>, 'SimulationSpeedQuarterWallClockTime': <SimulationSpeed.SimulationSpeedQuarterWallClockTime: 3>, 'SimulationSpeedWallClockTime': <SimulationSpeed.SimulationSpeedWallClockTime: 1>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class SkyLightPollution:
    """
    Members:

      SkyLightPollutionBrightSuburban

      SkyLightPollutionCity

      SkyLightPollutionDarkSite

      SkyLightPollutionInnerCity

      SkyLightPollutionNone

      SkyLightPollutionRural

      SkyLightPollutionRuralSuburban

      SkyLightPollutionSuburban

      SkyLightPollutionSuburbanUrban
    """

    SkyLightPollutionBrightSuburban: typing.ClassVar[
        SkyLightPollution
    ]  # value = <SkyLightPollution.SkyLightPollutionBrightSuburban: 6>
    SkyLightPollutionCity: typing.ClassVar[SkyLightPollution]  # value = <SkyLightPollution.SkyLightPollutionCity: 8>
    SkyLightPollutionDarkSite: typing.ClassVar[
        SkyLightPollution
    ]  # value = <SkyLightPollution.SkyLightPollutionDarkSite: 2>
    SkyLightPollutionInnerCity: typing.ClassVar[
        SkyLightPollution
    ]  # value = <SkyLightPollution.SkyLightPollutionInnerCity: 9>
    SkyLightPollutionNone: typing.ClassVar[SkyLightPollution]  # value = <SkyLightPollution.SkyLightPollutionNone: 0>
    SkyLightPollutionRural: typing.ClassVar[SkyLightPollution]  # value = <SkyLightPollution.SkyLightPollutionRural: 3>
    SkyLightPollutionRuralSuburban: typing.ClassVar[
        SkyLightPollution
    ]  # value = <SkyLightPollution.SkyLightPollutionRuralSuburban: 4>
    SkyLightPollutionSuburban: typing.ClassVar[
        SkyLightPollution
    ]  # value = <SkyLightPollution.SkyLightPollutionSuburban: 5>
    SkyLightPollutionSuburbanUrban: typing.ClassVar[
        SkyLightPollution
    ]  # value = <SkyLightPollution.SkyLightPollutionSuburbanUrban: 7>
    __members__: typing.ClassVar[
        dict[str, SkyLightPollution]
    ]  # value = {'SkyLightPollutionBrightSuburban': <SkyLightPollution.SkyLightPollutionBrightSuburban: 6>, 'SkyLightPollutionCity': <SkyLightPollution.SkyLightPollutionCity: 8>, 'SkyLightPollutionDarkSite': <SkyLightPollution.SkyLightPollutionDarkSite: 2>, 'SkyLightPollutionInnerCity': <SkyLightPollution.SkyLightPollutionInnerCity: 9>, 'SkyLightPollutionNone': <SkyLightPollution.SkyLightPollutionNone: 0>, 'SkyLightPollutionRural': <SkyLightPollution.SkyLightPollutionRural: 3>, 'SkyLightPollutionRuralSuburban': <SkyLightPollution.SkyLightPollutionRuralSuburban: 4>, 'SkyLightPollutionSuburban': <SkyLightPollution.SkyLightPollutionSuburban: 5>, 'SkyLightPollutionSuburbanUrban': <SkyLightPollution.SkyLightPollutionSuburbanUrban: 7>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class SkyType:
    """
    Members:

      DAY

      NIGHT

      DAWN

      DUSK
    """

    DAWN: typing.ClassVar[SkyType]  # value = <SkyType.DAWN: 0>
    DAY: typing.ClassVar[SkyType]  # value = <SkyType.DAY: 1>
    DUSK: typing.ClassVar[SkyType]  # value = <SkyType.DUSK: 2>
    NIGHT: typing.ClassVar[SkyType]  # value = <SkyType.NIGHT: 3>
    __members__: typing.ClassVar[
        dict[str, SkyType]
    ]  # value = {'DAY': <SkyType.DAY: 1>, 'NIGHT': <SkyType.NIGHT: 3>, 'DAWN': <SkyType.DAWN: 0>, 'DUSK': <SkyType.DUSK: 2>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class TrafficSide:
    """
    Members:

      TrafficSideTypeLeftHandTraffic

      TrafficSideTypeRightHandTraffic
    """

    TrafficSideTypeLeftHandTraffic: typing.ClassVar[
        TrafficSide
    ]  # value = <TrafficSide.TrafficSideTypeLeftHandTraffic: 1>
    TrafficSideTypeRightHandTraffic: typing.ClassVar[
        TrafficSide
    ]  # value = <TrafficSide.TrafficSideTypeRightHandTraffic: 0>
    __members__: typing.ClassVar[
        dict[str, TrafficSide]
    ]  # value = {'TrafficSideTypeLeftHandTraffic': <TrafficSide.TrafficSideTypeLeftHandTraffic: 1>, 'TrafficSideTypeRightHandTraffic': <TrafficSide.TrafficSideTypeRightHandTraffic: 0>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class Velocity:
    x: float
    y: float
    z: float
    def __array__(self) -> numpy.ndarray[numpy.float64]: ...
    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, x: float, y: float, z: float) -> None: ...
    @typing.overload
    def __init__(self, zero_init: bool) -> None:
        """
        Initialise with zeros or with NaNs
        """

    @typing.overload
    def __init__(self, array: numpy.ndarray[numpy.float64]) -> None: ...
    def __repr__(self) -> str: ...

class WeatherType:
    """
    Members:

      SUNNY

      RAINY

      SNOWY
    """

    RAINY: typing.ClassVar[WeatherType]  # value = <WeatherType.RAINY: 1>
    SNOWY: typing.ClassVar[WeatherType]  # value = <WeatherType.SNOWY: 2>
    SUNNY: typing.ClassVar[WeatherType]  # value = <WeatherType.SUNNY: 0>
    __members__: typing.ClassVar[
        dict[str, WeatherType]
    ]  # value = {'SUNNY': <WeatherType.SUNNY: 0>, 'RAINY': <WeatherType.RAINY: 1>, 'SNOWY': <WeatherType.SNOWY: 2>}
    def __eq__(self, other: typing.Any) -> bool: ...
    def __getstate__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __init__(self, value: int) -> None: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: typing.Any) -> bool: ...
    def __repr__(self) -> str: ...
    def __setstate__(self, state: int) -> None: ...
    def __str__(self) -> str: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class _AmesimDynamicalModel(_EntityModel):
    class Input:
        brake: float
        gear: Gear
        steering_wheel_angle: float
        throttle: float
        def __array__(self) -> numpy.ndarray[numpy.float64]: ...
        @typing.overload
        def __init__(self) -> None: ...
        @typing.overload
        def __init__(self, throttle: float, brake: float, steering_wheel_angle: float, gear: Gear) -> None: ...
        @typing.overload
        def __init__(self, array: numpy.ndarray[numpy.float64]) -> None: ...
        def __repr__(self) -> str: ...

    class Setup:
        existing: bool
        initial_velocity: float
        is_flat_ground: bool
        @typing.overload
        def __init__(self) -> None: ...
        @typing.overload
        def __init__(self, existing: bool, is_flat_ground: bool, initial_velocity: float) -> None: ...

    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, initial_input: _AmesimDynamicalModel.Input) -> None: ...
    @typing.overload
    def __init__(
        self, setup: _AmesimDynamicalModel.Setup, initial_input: _AmesimDynamicalModel.Input = ...
    ) -> None: ...
    def __repr__(self) -> str: ...
    def create_model(self, object: _WorldObject, experiment: _Experiment) -> None: ...
    def register_unit(self, object: _WorldObject, experiment: _Experiment, simulation: _ISimulation) -> None: ...
    @typing.overload
    def set_input(self, input: numpy.ndarray[numpy.float64]) -> None: ...
    @typing.overload
    def set_input(self, input: _AmesimDynamicalModel.Input) -> None: ...
    @typing.overload
    def update_input(self, input: numpy.ndarray[numpy.float64]) -> None: ...
    @typing.overload
    def update_input(self, input: _AmesimDynamicalModel.Input) -> None: ...
    @property
    def initial_velocity(self) -> float:
        """
        Initial velocity of the model
        """

    @property
    def is_flat_ground(self) -> bool:
        """
        Whether the model is just assum everything is a flat ground
        """

class _CustomDynamicalModel(_EntityModel):
    class Input:
        acceleration: Acceleration
        angular_velocity: AngularVelocity
        orientation: Orientation
        position: Position
        velocity: Velocity
        def __array__(self) -> numpy.ndarray[numpy.float64]: ...
        @typing.overload
        def __init__(self) -> None: ...
        @typing.overload
        def __init__(self, zero_init: bool) -> None: ...
        @typing.overload
        def __init__(
            self,
            position: Position,
            orientation: Orientation,
            acceleration: Acceleration,
            velocity: Velocity,
            angular_velocity: AngularVelocity,
        ) -> None: ...
        @typing.overload
        def __init__(self, array: numpy.ndarray[numpy.float64]) -> None: ...
        def __repr__(self) -> str: ...

    class Setup:
        existing: bool
        @typing.overload
        def __init__(self) -> None: ...
        @typing.overload
        def __init__(self, existing: bool) -> None: ...

    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, initial_input: _CustomDynamicalModel.Input) -> None: ...
    @typing.overload
    def __init__(
        self, setup: _CustomDynamicalModel.Setup, initial_input: _CustomDynamicalModel.Input = ...
    ) -> None: ...
    def __repr__(self) -> str: ...
    @typing.overload
    def set_input(self, input: numpy.ndarray[numpy.float64]) -> None: ...
    @typing.overload
    def set_input(self, input: _CustomDynamicalModel.Input) -> None: ...
    @typing.overload
    def update_input(self, input: numpy.ndarray[numpy.float64]) -> None: ...
    @typing.overload
    def update_input(self, input: _CustomDynamicalModel.Input) -> None: ...
    @property
    def input(self) -> _CustomDynamicalModel.Input: ...

class _Entity:
    class Setup:
        cog_offset: Position
        is_collision_detectable: bool
        is_movable: bool
        orientation: Orientation
        position: Position
        sensor_detectability: SensorDetectability
        def __array__(self) -> numpy.ndarray[numpy.float64]: ...
        @typing.overload
        def __init__(self) -> None: ...
        @typing.overload
        def __init__(
            self,
            position: Position,
            orientation: Orientation,
            cog_offset: Position,
            is_collision_detectable: bool,
            is_movable: bool,
            sensor_detectability: SensorDetectability,
        ) -> None: ...
        @typing.overload
        def __init__(
            self,
            zero_init: bool,
            is_collision_detectable: bool,
            is_movable: bool,
            sensor_detectability: SensorDetectability,
        ) -> None: ...
        @typing.overload
        def __init__(self, array: numpy.ndarray[numpy.float64]) -> None: ...
        def __repr__(self) -> str: ...

    class State:
        orientation: Orientation
        position: Position
        velocity: float
        yaw_rate: float
        def __array__(self) -> numpy.ndarray[numpy.float64]: ...
        @typing.overload
        def __init__(self) -> None: ...
        @typing.overload
        def __init__(self, position: Position, orientation: Orientation, velocity: float, yaw_rate: float) -> None: ...
        @typing.overload
        def __init__(self, zero_init: bool) -> None: ...
        @typing.overload
        def __init__(self, array: numpy.ndarray[numpy.float64]) -> None: ...
        def __repr__(self) -> str: ...

    def __init__(
        self, object_type: ObjectType, setup: _Entity.Setup = ..., entity_model: _EntityModel = None
    ) -> None: ...
    def __repr__(self) -> str: ...
    def add_sensor(self, sensor: _Sensor) -> None: ...
    @typing.overload
    def apply_setup(self) -> None: ...
    @typing.overload
    def apply_setup(self, setup: _Entity.Setup) -> None: ...
    def initialise(self, simulation: _ISimulation) -> None: ...
    def initialise_object(self, experiment: _Experiment, object: _WorldObject) -> None: ...
    def register_unit(self, experiment: _Experiment, simulation: _ISimulation) -> None: ...
    def remove(self) -> None:
        """
        Remove the object from the experiment
        """

    def step(self, simulation: _ISimulation) -> None: ...
    def terminate(self, simulation: _ISimulation) -> None: ...
    @property
    def is_initialised(self) -> bool:
        """
        Wether the world object has been initialised
        """

    @property
    def object(self) -> _WorldObject:
        """
        Get the worldobject wrapped by the entity
        """

    @property
    def setup(self) -> _Entity.Setup:
        """
        Get the current initial setup of the entity
        """

    @property
    def state(self) -> _Entity.State:
        """
        Get the current state of the entity
        """

    @property
    def type(self) -> ObjectType:
        """
        Get the type of the entity
        """

class _EntityModel:
    def __init__(self, arg0: bool) -> None: ...
    def create_model(self, object: _WorldObject, experiment: _Experiment) -> None:
        """
        Initialise the object of the model
        """

    def initialise(self, simulation: _ISimulation) -> None:
        """
        Called when the simulation is initialised
        """

    def register_unit(self, object: _WorldObject, experiment: _Experiment, simulation: _ISimulation) -> None:
        """
        Register the unit of the model
        """

    def set_input(self, input: list[float]) -> None:
        """
        Set the input of the model
        """

    def step(self, simulation: _ISimulation) -> None:
        """
        Called at each simulation step
        """

    def terminate(self, simulation: _ISimulation) -> None:
        """
        Called when the simulation is terminated
        """

    def update_input(self, input: list[float]) -> None:
        """
        Update the input of the model
        """

    @property
    def existing(self) -> bool:
        """
        Whether the model was already present in the experiment
        """

class _Environment:
    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, filename: str) -> None: ...
    @typing.overload
    def add_entity(self, entity: "_Entity") -> _Environment:
        """
        Add an entity to the environment
        """

    @typing.overload
    def add_entity(self, name: str, entity: "_Entity") -> _Environment:
        """
        Collect an existing entity from the experiment
        """

    def add_free_viewer(self) -> _Viewer:
        """
        Add a free viewer in the environment
        """

    def add_road(self, position: Position = None) -> Road:
        """
        Add a road to the environment
        """

    def import_open_drive_network(self, filename: str) -> _Environment:
        """
        Import an OpenDrive network from a file
        """

    def remove_all_viewers(self) -> None:
        """
        Remove all viewers from the environment
        """

    @typing.overload
    def remove_entity(self, entity: "_Entity") -> _Environment:
        """
        Add an entity to the environment
        """

    @typing.overload
    def remove_entity(self, name: str) -> _Environment:
        """
        Add an entity to the environment
        """

    def save_experiment(self, filename: str) -> None:
        """
        Save the experiment to file
        """

    def set_scheduler_frequencies(self, simulation_frequency: int, integration_frequency: int) -> _Environment:
        """
        Set the scheduler frequencies of the environment
        """

    def set_scheduler_speed(self, simulation_speed: SimulationSpeed, ignore_frame_overrun: bool) -> _Environment:
        """
        Set the scheduler speed of the environment
        """

    def set_sky(self, sky_type: SkyType = ..., light_pollution: SkyLightPollution = ...) -> _Environment:
        """
        Set the sky of the environment
        """

    def set_weather(self, weather_type: WeatherType = ..., fog_visibility: float = -1) -> _Environment:
        """
        Set the weather of the environment
        """

    @property
    def experiment(self) -> _Experiment:
        """
        Get the experiment of the environment
        """

class _Experiment:
    @staticmethod
    def create_experiment() -> _Experiment: ...
    @staticmethod
    def load_experiment_from_file(filename: str) -> _Experiment: ...
    def object_types(self) -> list[str]: ...

class _ISimulation:
    def get_sample_time(self) -> float: ...
    def get_simulation_path(self) -> str: ...
    def stop(self) -> None: ...

class _Sensor:
    @typing.overload
    def __init__(self, sensor_type: SensorType, existing: bool = False) -> None: ...
    @typing.overload
    def __init__(self, arg0: SensorType, arg1: numpy.ndarray[numpy.float64], arg2: bool) -> None: ...
    def create_sensor(self, object: _WorldObject, id: int) -> None: ...
    def initialise(self, simulation: _ISimulation) -> None: ...
    def register_unit(self, object: _WorldObject, experiment: _Experiment, simulation: _ISimulation) -> None: ...
    def step(self, simulation: _ISimulation) -> None: ...
    def terminate(self, simulation: _ISimulation) -> None: ...
    @property
    def sensor_type(self) -> SensorType: ...
    @property
    def setup(self) -> list[float]: ...
    @property
    def state(self) -> list[float]: ...

class _Simulation:
    def __init__(self, environment: _Environment) -> None: ...
    def initialise(self) -> None:
        """
        Initialise the simulation.
        """

    def remove_on_post_step(self) -> None:
        """
        Set a callback to be called as the last operation at each step.
        """

    def remove_on_pre_step(self) -> None:
        """
        Set a callback to be called as the first operation at each step.
        """

    def run(self, seconds: float = -1.0) -> None:
        """
        Run the simulation automatically.
        """

    def set_log_level(self, log_level: LogLevel) -> None:
        """
        Set the log level of the simulation logger.
        """

    def set_on_post_step(self, callback: typing.Callable[[], None]) -> None:
        """
        Set a callback to be called as the last operation at each step.
        """

    def set_on_pre_step(self, callback: typing.Callable[[], None]) -> None:
        """
        Set a callback to be called as the first operation at each step.
        """

    def step(self) -> None:
        """
        Advance the simulation manually.
        """

    def terminate(self) -> None:
        """
        Terminate the simulation and clean up.
        """

class _TrackModel(_EntityModel):
    class Setup:
        existing: bool
        path: list[Position]
        speed: float
        tolerance: float
        @typing.overload
        def __init__(self) -> None: ...
        @typing.overload
        def __init__(self, existing: bool, path: list[Position], speed: float, tolerance: float) -> None: ...

    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, setup: _TrackModel.Setup) -> None: ...
    def __repr__(self) -> str: ...

class _Unit:
    pass

class _Viewer:
    @staticmethod
    def create_viewer(experiment: _Experiment) -> _Viewer: ...
    def remove(self) -> None: ...
    def window_settings(self) -> _WindowSettings: ...

class _WindowSettings:
    always_on_top: bool
    fullscreen: bool
    height: int
    origin_x: int
    origin_y: int
    screen_id: int
    visualization_frequency: int
    width: int
    window_decoration: bool

class _WorldObject:
    cog_offset: Position
    collision_detectable: bool
    movable: bool
    name: str
    orientation: Orientation
    position: Position
    sensor_detectability: SensorDetectability
    def remove(self) -> None: ...

AsphaltToneDark: AsphaltTone  # value = <AsphaltTone.AsphaltToneDark: 1>
AsphaltToneDarker: AsphaltTone  # value = <AsphaltTone.AsphaltToneDarker: 2>
AsphaltToneLight: AsphaltTone  # value = <AsphaltTone.AsphaltToneLight: 3>
AsphaltToneLighter: AsphaltTone  # value = <AsphaltTone.AsphaltToneLighter: 4>
AsphaltToneStandard: AsphaltTone  # value = <AsphaltTone.AsphaltToneStandard: 0>
AsphaltTypeColoredTexture: AsphaltType  # value = <AsphaltType.AsphaltTypeColoredTexture: 2>
AsphaltTypeSingleColor: AsphaltType  # value = <AsphaltType.AsphaltTypeSingleColor: 1>
AsphaltTypeStandard: AsphaltType  # value = <AsphaltType.AsphaltTypeStandard: 0>
Forward: Gear  # value = <Gear.Forward: 1>
LaneSideTypeInner: LaneSideType  # value = <LaneSideType.LaneSideTypeInner: 0>
LaneSideTypeOuter: LaneSideType  # value = <LaneSideType.LaneSideTypeOuter: 1>
LaneTypeBiking: LaneType  # value = <LaneType.LaneTypeBiking: 1>
LaneTypeDriving: LaneType  # value = <LaneType.LaneTypeDriving: 0>
LaneTypeSideWalk: LaneType  # value = <LaneType.LaneTypeSideWalk: 2>
LogLevelClean: LogLevel  # value = <LogLevel.LogLevelClean: 7>
LogLevelCrawl: LogLevel  # value = <LogLevel.LogLevelCrawl: 0>
LogLevelCritical: LogLevel  # value = <LogLevel.LogLevelCritical: 6>
LogLevelDebug: LogLevel  # value = <LogLevel.LogLevelDebug: 1>
LogLevelError: LogLevel  # value = <LogLevel.LogLevelError: 5>
LogLevelInfo: LogLevel  # value = <LogLevel.LogLevelInfo: 2>
LogLevelInherit: LogLevel  # value = <LogLevel.LogLevelInherit: 9>
LogLevelNotice: LogLevel  # value = <LogLevel.LogLevelNotice: 3>
LogLevelOff: LogLevel  # value = <LogLevel.LogLevelOff: 8>
LogLevelWarning: LogLevel  # value = <LogLevel.LogLevelWarning: 4>
Neutral: Gear  # value = <Gear.Neutral: 0>
ParamPolyRangeTypeArcLength: ParameterRange  # value = <ParameterRange.ParamPolyRangeTypeArcLength: 0>
ParamPolyRangeTypeNormalized: ParameterRange  # value = <ParameterRange.ParamPolyRangeTypeNormalized: 1>
Reverse: Gear  # value = <Gear.Reverse: -1>
RoadSideTypeLeft: RoadSideType  # value = <RoadSideType.RoadSideTypeLeft: 0>
RoadSideTypeRight: RoadSideType  # value = <RoadSideType.RoadSideTypeRight: 1>
SensorDetectabilityDetectable: SensorDetectability  # value = <SensorDetectability.SensorDetectabilityDetectable: 2>
SensorDetectabilityInvisible: SensorDetectability  # value = <SensorDetectability.SensorDetectabilityInvisible: 0>
SensorDetectabilityOccluding: SensorDetectability  # value = <SensorDetectability.SensorDetectabilityOccluding: 1>
SimulationSpeedAsFastAsPossible: SimulationSpeed  # value = <SimulationSpeed.SimulationSpeedAsFastAsPossible: 0>
SimulationSpeedHalfWallClockTime: SimulationSpeed  # value = <SimulationSpeed.SimulationSpeedHalfWallClockTime: 2>
SimulationSpeedQuarterWallClockTime: SimulationSpeed  # value = <SimulationSpeed.SimulationSpeedQuarterWallClockTime: 3>
SimulationSpeedWallClockTime: SimulationSpeed  # value = <SimulationSpeed.SimulationSpeedWallClockTime: 1>
SkyLightPollutionBrightSuburban: SkyLightPollution  # value = <SkyLightPollution.SkyLightPollutionBrightSuburban: 6>
SkyLightPollutionCity: SkyLightPollution  # value = <SkyLightPollution.SkyLightPollutionCity: 8>
SkyLightPollutionDarkSite: SkyLightPollution  # value = <SkyLightPollution.SkyLightPollutionDarkSite: 2>
SkyLightPollutionInnerCity: SkyLightPollution  # value = <SkyLightPollution.SkyLightPollutionInnerCity: 9>
SkyLightPollutionNone: SkyLightPollution  # value = <SkyLightPollution.SkyLightPollutionNone: 0>
SkyLightPollutionRural: SkyLightPollution  # value = <SkyLightPollution.SkyLightPollutionRural: 3>
SkyLightPollutionRuralSuburban: SkyLightPollution  # value = <SkyLightPollution.SkyLightPollutionRuralSuburban: 4>
SkyLightPollutionSuburban: SkyLightPollution  # value = <SkyLightPollution.SkyLightPollutionSuburban: 5>
SkyLightPollutionSuburbanUrban: SkyLightPollution  # value = <SkyLightPollution.SkyLightPollutionSuburbanUrban: 7>
TrafficSideTypeLeftHandTraffic: TrafficSide  # value = <TrafficSide.TrafficSideTypeLeftHandTraffic: 1>
TrafficSideTypeRightHandTraffic: TrafficSide  # value = <TrafficSide.TrafficSideTypeRightHandTraffic: 0>
Undefined: Gear  # value = <Gear.Undefined: 2>
__version__: str = "0.0.1"
