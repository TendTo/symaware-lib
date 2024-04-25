/**
 * @file environment.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Environment class.
 */
#pragma once

#include <cstdint>
#include <prescan/api/Viewer.hpp>
#include <prescan/api/experiment.hpp>
#include <string>
#include <vector>

#include "symaware/prescan/data.h"

namespace symaware {

// Forward declaration
class Entity;

class Environment {
 public:
  enum class WeatherType { SUNNY, RAINY, SNOWY };
  enum class SkyType { DAWN, DAY, DUSK, NIGHT };
  enum class ObjectType {
    ADAC_target_yellow_merc,
    ApartmentBuilding,
    ArrowBoard_Trailer,
    Ash10y,
    Ash20y,
    Audi_A3,
    Audi_A8_Sedan,
    AustrianPine10y,
    AustrianPine20y,
    BE_Police_Volvo_XC60,
    BMW_X5_SUV,
    BMW_Z3_Convertible,
    BalloonCar,
    BarrierFence,
    Birch10y,
    Birch20y,
    BlueSpruce10y,
    BlueSpruce20y,
    BottsDots_White,
    BottsDots_Yellow,
    Boy_100,
    Boy_150,
    Building_00A,
    Building_01A,
    Building_02A,
    Building_03A,
    Building_04A,
    Building_05A,
    Building_06A,
    Building_07A,
    Building_08A,
    Busstop,
    CAT_725,
    Cadillac_Escalade,
    CarDealer,
    Car_Trailer_Small,
    CatsEyesR,
    CatsEyesW,
    CatsEyesWR,
    CatsEyesWY,
    CatsEyesY,
    Child_Leaning,
    Child_Overweight,
    Child_Regular,
    Child_Sitting,
    CinderBlock_A,
    CinderBlock_B,
    CinderBlock_C,
    Citroen_C3_Hatchback,
    ConstructionSign_JP,
    Container_Trailer,
    CornerReflector138mm,
    CornerReflector176_8mm,
    CornerReflector46_35mm,
    Cotton_A,
    Cotton_B,
    Cotton_C,
    DAF_95_XF,
    DAF_Euro_6_XF,
    Deer,
    Dogwood10y,
    Dogwood20y,
    Dumpster_2300L,
    DutchChurch,
    Empty_Light_Node,
    FAW_Jiefang_J6M,
    FShape150cm,
    FShape250cm,
    FShape350cm,
    Female_Bending,
    Female_Leaning,
    Female_Overweight,
    Female_Regular,
    Female_wBuggy,
    Female_wLongCoat,
    Female_wRaincoat,
    Female_wShoppingCart,
    Fiat_Bravo_Hatchback,
    FireBrigade,
    Ford_Fiesta_Hatchback,
    Ford_Focus_Stationwagon,
    Full_Trailer,
    Garage_Ground_Floor,
    Garage_Mid_Floor,
    Garage_Top_Floor,
    GasStation,
    Genesis_GV80,
    GuardrailReflector_RectR,
    GuardrailReflector_RectW,
    GuardrailReflector_RectWR,
    GuardrailReflector_RoundR,
    GuardrailReflector_RoundW,
    GuardrailReflector_RoundWR,
    GuardrailReflector_RoundY,
    GuidedSoftTarget,
    HOWO_T5G_Cement_Truck,
    Hino_Blue_Ribbon,
    Honda_Pan_European_Motorcycle,
    Honda_Pan_European_Motorcycle_With_Driver,
    HouseModern,
    HouseOld1,
    HouseOld2,
    HouseOld3,
    HouseOld4,
    HouseOld5,
    HouseOld6,
    Houses1930s,
    Hyundai_Ioniq5,
    Hyundai_i30_NLine,
    Isuzu_DMax,
    Isuzu_Giga_Fire_Truck,
    JAC_HFC_Series,
    JapaneseMaple10y,
    JapaneseMaple20y,
    Joby_Aviation_S4,
    Kia_EV6,
    Kia_EV6_wRoofRack,
    Kia_EV6_wRoofRack_Siemens,
    Lexus_GS_450h_F_Sport_Sedan,
    Lexus_LS_600h_F_Sport,
    LightPost,
    Lilac10y,
    Lilac20y,
    Magnolia10y,
    Magnolia20y,
    Male_200,
    Male_African,
    Male_Bending,
    Male_BendingOver,
    Male_CyclingCyclist,
    Male_Female_HandInHand,
    Male_LargeShoulderSuitcase,
    Male_Leaning,
    Male_LeaningBack,
    Male_LyingDown,
    Male_Old_White_WithStick,
    Male_Old_White_WithWalker,
    Male_Old_White_WithWalkerWithWheels,
    Male_Overweight,
    Male_Regular,
    Male_ShoppingBag,
    Male_Sitting,
    Male_wBackpack,
    Male_wBicycle,
    Male_wLargeBackpack,
    Male_wLongCoat,
    Male_wRaincoat,
    Male_wSuit,
    Male_wSuitcase,
    Man_250,
    Man_Asian,
    Mazda_RX8_Coupe,
    MercedesBenz_Actros_1851_LS_4x2,
    MercedesBenz_Actros_1860_LS_4x2,
    MercedesBenz_Actros_2541_L_6x2,
    Mitsubishi_Outlander_PHEV,
    Monument,
    NCAP_Adult,
    NCAP_Child,
    NCAP_Cyclist,
    NCAP_EBTA,
    NCAP_GVT,
    NCAP_Motorcycle,
    NCAP_Scooter,
    NCAP_StreetLight,
    NL_Ambulance_Volvo_XC60,
    Nissan_Ariya,
    Nissan_Cabstar_Boxtruck,
    OfficeBrownFlat,
    OfficeBrownTall1,
    OfficeBrownTall2,
    OfficeGreenTall,
    Overhang1Light_JP,
    Overhang1Light_KR,
    Overhang1Light_NL,
    Overhang1Light_US,
    Overhang1Post_JP,
    Overhang1Post_KR,
    Overhang1Post_NL,
    Overhang1Post_US,
    Overhang2Lights_JP,
    Overhang2Lights_KR,
    Overhang2Lights_NL,
    Overhang2Lights_US,
    Overhang2Post_JP,
    Overhang2Post_KR,
    Overhang2Post_NL,
    Overhang2Post_US,
    OverhangDH2Lights_US,
    OverhangDHPost_US,
    Pallet,
    PedestrianSignal_JP,
    Peterbilt_579,
    Peterbilt_579_Trailer,
    PlasticBarrier100cm,
    PrismSignV_30_50_70,
    PrismSignV_5_10_15,
    PrismSignV_80_100_110,
    PrismSign_30_50_70,
    PrismSign_5_10_15,
    PrismSign_80_100_110,
    Pylon_01,
    Pylon_02,
    ReflectorSign,
    ReflectorSignSimple,
    Rivian_R1T,
    Rivian_R1T_wCover,
    RoadClosed_wLights,
    RoadsideLight_NL,
    RoadsideMarker,
    RoadsidePost,
    RoadsidePost_NL,
    Roewe_550_S_Sedan,
    Row_Crop_Tractor,
    School,
    Scooter,
    Scooter_wBox,
    Serviceberry10y,
    Serviceberry15y,
    Serviceberry5y,
    ShoppingCart,
    Siemens_eRod,
    SignalCasing20cm_NL,
    SignalCasing30cmDH_US,
    SignalCasing30cm_JP,
    SignalCasing30cm_NL,
    SignalCasing30cm_US,
    SignalCasing3_30cm_KR,
    SignalCasing4_30cm_KR,
    Skywell,
    SpeedBump250cm,
    SpeedBump350cm,
    Sports_Bike,
    Sports_Bike_wDriver,
    SpringPost46cm,
    SpringPost75cm,
    SpringPost95cm,
    Suzuki_Hustler_Hybrid,
    TerracedHouses,
    Tesla_Model_3,
    Tire_Horizontal,
    Tire_Vertical,
    Toddler_050,
    Toyota_Previa_MPV,
    Toyota_Prius_Sedan,
    Toyota_Yaris_Hatchback,
    TrashBin_240L,
    TrashCan_Rnd_130L,
    TrashCan_Sqr_160L,
    TriangleParkingSpaceLock,
    TurkishHazel10y,
    TurkishHazel20y,
    US_Police_Volvo_XC60,
    VehicleSignal30cm_FL_JP,
    VehicleSignal30cm_FR_JP,
    VehicleSignal30cm_F_JP,
    VehicleSignal30cm_L_JP,
    VehicleSignal30cm_R_JP,
    VehicleSignalGreen30cm_JP,
    VehicleSignalOrange30cm_JP,
    VehicleSignalRed30cm_JP,
    Volvo_FH16,
    Volvo_XC60,
    Warehouse,
    Wheat_A,
    Wheat_B,
    Wheat_C,
    WheelieBin_1100L,
    Windmill,
    Wuling_Hongguang,
    Church,
    Factory,
    ConcreteGuardrail,
    Guardrail,
    Fence,
    LinePlacedRoadImperfection,
    SoundAbsorbingWall,
    Wall,
    House,
    Office,
    Box,
    Capsule,
    Cone,
    Cylinder,
    Sphere,
    Tripod,
    TrafficSignPole
  };

  Environment();
  explicit Environment(const std::string& file_path);

  /**
   * @brief Set the environment weather to the specified type and fog visibility
   *
   * A negative value for fog_visibility will disable the fog all together
   * @param weather_type type of weather
   * @param fog_visibility visibility of the fog
   * @return reference to the environment
   */
  Environment& setWeather(WeatherType weather_type = WeatherType::SUNNY, double fog_visibility = -1);
  /**
   * @brief Set the environment sky to the specified type and light pollution
   * @param sky_type moment of the day
   * @param light_pollution level of light pollution. Can be disabled with SkyLightPollutionNone
   * @return reference to the environment
   */
  Environment& setSky(SkyType sky_type = SkyType::DAY,
                      prescan::api::types::SkyLightPollution light_pollution =
                          prescan::api::types::SkyLightPollution::SkyLightPollutionNone);
  /**
   * @brief Set the scheduler frequencies
   *
   * Only used if the simulation step is not handled manually by the user
   * @param simulation_frequency the frequency at which the simulation will run
   * @param integration_frequency the frequency at which the integration will run
   * @return reference to the environment
   */
  Environment& setScheduler(std::int32_t simulation_frequency, std::int32_t integration_frequency);

  /**
   * @brief Create a free camera viewer for the environment.
   *
   * The viewer will allow for the visualisation of the environment using the Prescan viewer using a free camera.
   * @return the new viewer
   */
  prescan::api::viewer::Viewer createFreeViewer();
  /**
   * @brief Remove all viewers from the environment.
   * @warning All previously created viewers will be invalidated
   */
  void removeAllViewers();

  /**
   * @brief Add an entity to the environment.
   *
   * The entity will be placed in the world at the specified position and orientation.
   * If the operation is successful, the @p entity will be initialised with the object created in the simulation.
   * Futhermore, if the @p entity is controllable, meaning it is associated with a dynamical model,
   * it will be registered in the simulation as a controllable agent.
   * @param[in,out] entity entity representing the new object to be added
   * The entity will be initialised with the object created in the simulation
   * @param position position of the object in the world
   */
  Environment& addEntity(Entity& entity);

  /**
   * @brief Get the experiment object of the environment
   * @return experiment object
   */
  const prescan::api::experiment::Experiment& experiment() const { return experiment_; }

  /**
   * @brief Get the names of the entities in the environment
   * @return names of the entities
   */
  const std::vector<Entity*>& entities() const { return entities_; }

  /**
   * @brief Get an object from the environment by name
   * @tparam T type of object
   * @param object_name name of the object
   * @return object
   * @throw std::runtime_error if the object does not exist
   */
  template <class T>
  T getObject(const std::string& object_name) {
    return experiment_.getObjectByName<T>(object_name);
  }

 private:
  prescan::api::experiment::Experiment experiment_;
  std::vector<Entity*> entities_;
};

std::string to_string(Environment::WeatherType weather_type);
std::string to_string(Environment::SkyType sky_type);
std::string to_string(Environment::ObjectType object_type);

}  // namespace symaware
