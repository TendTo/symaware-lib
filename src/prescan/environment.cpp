#include "symaware/prescan/environment.h"

#include <iostream>

#include "symaware/util/exception.h"

namespace symaware {

Environment::Environment() : experiment_{prescan::api::experiment::createExperiment()} {}

void Environment::setWeather(const WeatherType weather_type, const double fog_visibility) {
  prescan::api::types::Weather weather{experiment_.weather()};
  switch (weather_type) {
    case WeatherType::SUNNY:
      weather.precipitation().setDisabled();
      break;
    case WeatherType::RAINY:
      weather.precipitation().setDefaultRain();
      break;
    case WeatherType::SNOWY:
      weather.precipitation().setDefaultSnow();
      break;
    default:
      SYMAWARE_UNREACHABLE();
  }
  if (fog_visibility < 0) {
    weather.fog().setEnabled(false);
  } else {
    weather.fog().setEnabled(true);
    weather.fog().setVisibility(fog_visibility);
  }
}

void Environment::setSky(const SkyType sky_type, const prescan::api::types::SkyLightPollution light_pollution) {
  prescan::api::types::Sky sky{experiment_.sky()};
  switch (sky_type) {
    case SkyType::DAWN:
      sky.setPresetDawn();
      break;
    case SkyType::DAY:
      sky.setPresetDay();
      break;
    case SkyType::DUSK:
      sky.setPresetDusk();
      break;
    case SkyType::NIGHT:
      sky.setPresetNight();
      break;
    default:
      SYMAWARE_UNREACHABLE();
  }
  sky.setLightPollution(light_pollution);
}

void Environment::setScheduler(const std::int32_t simulation_frequency, const std::int32_t integration_frequency) {
  experiment_.scheduler().setFrequencies(simulation_frequency, integration_frequency);
}

std::string Environment::addObject(const ObjectType object_type, const Orientation& orientation, const bool movable) {
  return addObject(object_type, {0, 0, 0}, orientation, movable);
}
std::string Environment::addObject(const ObjectType object_type, const bool movable) {
  return addObject(object_type, {0, 0, 0}, {0, 0, 0}, movable);
}
std::string Environment::addObject(const ObjectType object_type, const Position& position,
                                   const Orientation& orientation, const bool movable) {
  prescan::api::types::WorldObject object{experiment_.createObject(to_string(object_type))};
  object.setMovable(movable);
  object.pose().orientation().setRPY(orientation.roll, orientation.pitch, orientation.yaw);
  object.pose().position().setXYZ(position.x, position.y, position.z);
  return object.name();
}

const std::string& Environment::addAgent(const ObjectType object_type, const Position& position,
                                         const Orientation& orientation) {
  controllable_agents_.emplace_back(addObject(object_type, position, orientation, true));
  return controllable_agents_.back();
}
const std::string& Environment::addAgent(const ObjectType object_type, const Orientation& orientation) {
  controllable_agents_.emplace_back(addObject(object_type, orientation, true));
  return controllable_agents_.back();
}

std::string to_string(const Environment::WeatherType weather_type) {
  switch (weather_type) {
    case Environment::WeatherType::SUNNY:
      return "Sunny";
    case Environment::WeatherType::RAINY:
      return "Rainy";
    case Environment::WeatherType::SNOWY:
      return "Snowy";
    default:
      SYMAWARE_UNREACHABLE();
  }
}
std::string to_string(const Environment::SkyType sky_type) {
  switch (sky_type) {
    case Environment::SkyType::DAWN:
      return "Dawn";
    case Environment::SkyType::DAY:
      return "Day";
    case Environment::SkyType::DUSK:
      return "Dusk";
    case Environment::SkyType::NIGHT:
      return "Night";
    default:
      SYMAWARE_UNREACHABLE();
  }
}
std::string to_string(const Environment::ObjectType object_type) {
  switch (object_type) {
    case Environment::ObjectType::ADAC_target_yellow_merc:
      return "ADAC_target_yellow_merc";
    case Environment::ObjectType::ApartmentBuilding:
      return "ApartmentBuilding";
    case Environment::ObjectType::ArrowBoard_Trailer:
      return "ArrowBoard_Trailer";
    case Environment::ObjectType::Ash10y:
      return "Ash10y";
    case Environment::ObjectType::Ash20y:
      return "Ash20y";
    case Environment::ObjectType::Audi_A3:
      return "Audi_A3";
    case Environment::ObjectType::Audi_A8_Sedan:
      return "Audi_A8_Sedan";
    case Environment::ObjectType::AustrianPine10y:
      return "AustrianPine10y";
    case Environment::ObjectType::AustrianPine20y:
      return "AustrianPine20y";
    case Environment::ObjectType::BE_Police_Volvo_XC60:
      return "BE_Police_Volvo_XC60";
    case Environment::ObjectType::BMW_X5_SUV:
      return "BMW_X5_SUV";
    case Environment::ObjectType::BMW_Z3_Convertible:
      return "BMW_Z3_Convertible";
    case Environment::ObjectType::BalloonCar:
      return "BalloonCar";
    case Environment::ObjectType::BarrierFence:
      return "BarrierFence";
    case Environment::ObjectType::Birch10y:
      return "Birch10y";
    case Environment::ObjectType::Birch20y:
      return "Birch20y";
    case Environment::ObjectType::BlueSpruce10y:
      return "BlueSpruce10y";
    case Environment::ObjectType::BlueSpruce20y:
      return "BlueSpruce20y";
    case Environment::ObjectType::BottsDots_White:
      return "BottsDots_White";
    case Environment::ObjectType::BottsDots_Yellow:
      return "BottsDots_Yellow";
    case Environment::ObjectType::Boy_100:
      return "Boy_100";
    case Environment::ObjectType::Boy_150:
      return "Boy_150";
    case Environment::ObjectType::Building_00A:
      return "Building_00A";
    case Environment::ObjectType::Building_01A:
      return "Building_01A";
    case Environment::ObjectType::Building_02A:
      return "Building_02A";
    case Environment::ObjectType::Building_03A:
      return "Building_03A";
    case Environment::ObjectType::Building_04A:
      return "Building_04A";
    case Environment::ObjectType::Building_05A:
      return "Building_05A";
    case Environment::ObjectType::Building_06A:
      return "Building_06A";
    case Environment::ObjectType::Building_07A:
      return "Building_07A";
    case Environment::ObjectType::Building_08A:
      return "Building_08A";
    case Environment::ObjectType::Busstop:
      return "Busstop";
    case Environment::ObjectType::CAT_725:
      return "CAT_725";
    case Environment::ObjectType::Cadillac_Escalade:
      return "Cadillac_Escalade";
    case Environment::ObjectType::CarDealer:
      return "CarDealer";
    case Environment::ObjectType::Car_Trailer_Small:
      return "Car_Trailer_Small";
    case Environment::ObjectType::CatsEyesR:
      return "CatsEyesR";
    case Environment::ObjectType::CatsEyesW:
      return "CatsEyesW";
    case Environment::ObjectType::CatsEyesWR:
      return "CatsEyesWR";
    case Environment::ObjectType::CatsEyesWY:
      return "CatsEyesWY";
    case Environment::ObjectType::CatsEyesY:
      return "CatsEyesY";
    case Environment::ObjectType::Child_Leaning:
      return "Child_Leaning";
    case Environment::ObjectType::Child_Overweight:
      return "Child_Overweight";
    case Environment::ObjectType::Child_Regular:
      return "Child_Regular";
    case Environment::ObjectType::Child_Sitting:
      return "Child_Sitting";
    case Environment::ObjectType::CinderBlock_A:
      return "CinderBlock_A";
    case Environment::ObjectType::CinderBlock_B:
      return "CinderBlock_B";
    case Environment::ObjectType::CinderBlock_C:
      return "CinderBlock_C";
    case Environment::ObjectType::Citroen_C3_Hatchback:
      return "Citroen_C3_Hatchback";
    case Environment::ObjectType::ConstructionSign_JP:
      return "ConstructionSign_JP";
    case Environment::ObjectType::Container_Trailer:
      return "Container_Trailer";
    case Environment::ObjectType::CornerReflector138mm:
      return "CornerReflector138mm";
    case Environment::ObjectType::CornerReflector176_8mm:
      return "CornerReflector176_8mm";
    case Environment::ObjectType::CornerReflector46_35mm:
      return "CornerReflector46_35mm";
    case Environment::ObjectType::Cotton_A:
      return "Cotton_A";
    case Environment::ObjectType::Cotton_B:
      return "Cotton_B";
    case Environment::ObjectType::Cotton_C:
      return "Cotton_C";
    case Environment::ObjectType::DAF_95_XF:
      return "DAF_95_XF";
    case Environment::ObjectType::DAF_Euro_6_XF:
      return "DAF_Euro_6_XF";
    case Environment::ObjectType::Deer:
      return "Deer";
    case Environment::ObjectType::Dogwood10y:
      return "Dogwood10y";
    case Environment::ObjectType::Dogwood20y:
      return "Dogwood20y";
    case Environment::ObjectType::Dumpster_2300L:
      return "Dumpster_2300L";
    case Environment::ObjectType::DutchChurch:
      return "DutchChurch";
    case Environment::ObjectType::Empty_Light_Node:
      return "Empty_Light_Node";
    case Environment::ObjectType::FAW_Jiefang_J6M:
      return "FAW_Jiefang_J6M";
    case Environment::ObjectType::FShape150cm:
      return "FShape150cm";
    case Environment::ObjectType::FShape250cm:
      return "FShape250cm";
    case Environment::ObjectType::FShape350cm:
      return "FShape350cm";
    case Environment::ObjectType::Female_Bending:
      return "Female_Bending";
    case Environment::ObjectType::Female_Leaning:
      return "Female_Leaning";
    case Environment::ObjectType::Female_Overweight:
      return "Female_Overweight";
    case Environment::ObjectType::Female_Regular:
      return "Female_Regular";
    case Environment::ObjectType::Female_wBuggy:
      return "Female_wBuggy";
    case Environment::ObjectType::Female_wLongCoat:
      return "Female_wLongCoat";
    case Environment::ObjectType::Female_wRaincoat:
      return "Female_wRaincoat";
    case Environment::ObjectType::Female_wShoppingCart:
      return "Female_wShoppingCart";
    case Environment::ObjectType::Fiat_Bravo_Hatchback:
      return "Fiat_Bravo_Hatchback";
    case Environment::ObjectType::FireBrigade:
      return "FireBrigade";
    case Environment::ObjectType::Ford_Fiesta_Hatchback:
      return "Ford_Fiesta_Hatchback";
    case Environment::ObjectType::Ford_Focus_Stationwagon:
      return "Ford_Focus_Stationwagon";
    case Environment::ObjectType::Full_Trailer:
      return "Full_Trailer";
    case Environment::ObjectType::Garage_Ground_Floor:
      return "Garage_Ground_Floor";
    case Environment::ObjectType::Garage_Mid_Floor:
      return "Garage_Mid_Floor";
    case Environment::ObjectType::Garage_Top_Floor:
      return "Garage_Top_Floor";
    case Environment::ObjectType::GasStation:
      return "GasStation";
    case Environment::ObjectType::Genesis_GV80:
      return "Genesis_GV80";
    case Environment::ObjectType::GuardrailReflector_RectR:
      return "GuardrailReflector_RectR";
    case Environment::ObjectType::GuardrailReflector_RectW:
      return "GuardrailReflector_RectW";
    case Environment::ObjectType::GuardrailReflector_RectWR:
      return "GuardrailReflector_RectWR";
    case Environment::ObjectType::GuardrailReflector_RoundR:
      return "GuardrailReflector_RoundR";
    case Environment::ObjectType::GuardrailReflector_RoundW:
      return "GuardrailReflector_RoundW";
    case Environment::ObjectType::GuardrailReflector_RoundWR:
      return "GuardrailReflector_RoundWR";
    case Environment::ObjectType::GuardrailReflector_RoundY:
      return "GuardrailReflector_RoundY";
    case Environment::ObjectType::GuidedSoftTarget:
      return "GuidedSoftTarget";
    case Environment::ObjectType::HOWO_T5G_Cement_Truck:
      return "HOWO_T5G_Cement_Truck";
    case Environment::ObjectType::Hino_Blue_Ribbon:
      return "Hino_Blue_Ribbon";
    case Environment::ObjectType::Honda_Pan_European_Motorcycle:
      return "Honda_Pan_European_Motorcycle";
    case Environment::ObjectType::Honda_Pan_European_Motorcycle_With_Driver:
      return "Honda_Pan_European_Motorcycle_With_Driver";
    case Environment::ObjectType::HouseModern:
      return "HouseModern";
    case Environment::ObjectType::HouseOld1:
      return "HouseOld1";
    case Environment::ObjectType::HouseOld2:
      return "HouseOld2";
    case Environment::ObjectType::HouseOld3:
      return "HouseOld3";
    case Environment::ObjectType::HouseOld4:
      return "HouseOld4";
    case Environment::ObjectType::HouseOld5:
      return "HouseOld5";
    case Environment::ObjectType::HouseOld6:
      return "HouseOld6";
    case Environment::ObjectType::Houses1930s:
      return "Houses1930s";
    case Environment::ObjectType::Hyundai_Ioniq5:
      return "Hyundai_Ioniq5";
    case Environment::ObjectType::Hyundai_i30_NLine:
      return "Hyundai_i30_NLine";
    case Environment::ObjectType::Isuzu_DMax:
      return "Isuzu_DMax";
    case Environment::ObjectType::Isuzu_Giga_Fire_Truck:
      return "Isuzu_Giga_Fire_Truck";
    case Environment::ObjectType::JAC_HFC_Series:
      return "JAC_HFC_Series";
    case Environment::ObjectType::JapaneseMaple10y:
      return "JapaneseMaple10y";
    case Environment::ObjectType::JapaneseMaple20y:
      return "JapaneseMaple20y";
    case Environment::ObjectType::Joby_Aviation_S4:
      return "Joby_Aviation_S4";
    case Environment::ObjectType::Kia_EV6:
      return "Kia_EV6";
    case Environment::ObjectType::Kia_EV6_wRoofRack:
      return "Kia_EV6_wRoofRack";
    case Environment::ObjectType::Kia_EV6_wRoofRack_Siemens:
      return "Kia_EV6_wRoofRack_Siemens";
    case Environment::ObjectType::Lexus_GS_450h_F_Sport_Sedan:
      return "Lexus_GS_450h_F_Sport_Sedan";
    case Environment::ObjectType::Lexus_LS_600h_F_Sport:
      return "Lexus_LS_600h_F_Sport";
    case Environment::ObjectType::LightPost:
      return "LightPost";
    case Environment::ObjectType::Lilac10y:
      return "Lilac10y";
    case Environment::ObjectType::Lilac20y:
      return "Lilac20y";
    case Environment::ObjectType::Magnolia10y:
      return "Magnolia10y";
    case Environment::ObjectType::Magnolia20y:
      return "Magnolia20y";
    case Environment::ObjectType::Male_200:
      return "Male_200";
    case Environment::ObjectType::Male_African:
      return "Male_African";
    case Environment::ObjectType::Male_Bending:
      return "Male_Bending";
    case Environment::ObjectType::Male_BendingOver:
      return "Male_BendingOver";
    case Environment::ObjectType::Male_CyclingCyclist:
      return "Male_CyclingCyclist";
    case Environment::ObjectType::Male_Female_HandInHand:
      return "Male_Female_HandInHand";
    case Environment::ObjectType::Male_LargeShoulderSuitcase:
      return "Male_LargeShoulderSuitcase";
    case Environment::ObjectType::Male_Leaning:
      return "Male_Leaning";
    case Environment::ObjectType::Male_LeaningBack:
      return "Male_LeaningBack";
    case Environment::ObjectType::Male_LyingDown:
      return "Male_LyingDown";
    case Environment::ObjectType::Male_Old_White_WithStick:
      return "Male_Old_White_WithStick";
    case Environment::ObjectType::Male_Old_White_WithWalker:
      return "Male_Old_White_WithWalker";
    case Environment::ObjectType::Male_Old_White_WithWalkerWithWheels:
      return "Male_Old_White_WithWalkerWithWheels";
    case Environment::ObjectType::Male_Overweight:
      return "Male_Overweight";
    case Environment::ObjectType::Male_Regular:
      return "Male_Regular";
    case Environment::ObjectType::Male_ShoppingBag:
      return "Male_ShoppingBag";
    case Environment::ObjectType::Male_Sitting:
      return "Male_Sitting";
    case Environment::ObjectType::Male_wBackpack:
      return "Male_wBackpack";
    case Environment::ObjectType::Male_wBicycle:
      return "Male_wBicycle";
    case Environment::ObjectType::Male_wLargeBackpack:
      return "Male_wLargeBackpack";
    case Environment::ObjectType::Male_wLongCoat:
      return "Male_wLongCoat";
    case Environment::ObjectType::Male_wRaincoat:
      return "Male_wRaincoat";
    case Environment::ObjectType::Male_wSuit:
      return "Male_wSuit";
    case Environment::ObjectType::Male_wSuitcase:
      return "Male_wSuitcase";
    case Environment::ObjectType::Man_250:
      return "Man_250";
    case Environment::ObjectType::Man_Asian:
      return "Man_Asian";
    case Environment::ObjectType::Mazda_RX8_Coupe:
      return "Mazda_RX8_Coupe";
    case Environment::ObjectType::MercedesBenz_Actros_1851_LS_4x2:
      return "MercedesBenz_Actros_1851_LS_4x2";
    case Environment::ObjectType::MercedesBenz_Actros_1860_LS_4x2:
      return "MercedesBenz_Actros_1860_LS_4x2";
    case Environment::ObjectType::MercedesBenz_Actros_2541_L_6x2:
      return "MercedesBenz_Actros_2541_L_6x2";
    case Environment::ObjectType::Mitsubishi_Outlander_PHEV:
      return "Mitsubishi_Outlander_PHEV";
    case Environment::ObjectType::Monument:
      return "Monument";
    case Environment::ObjectType::NCAP_Adult:
      return "NCAP_Adult";
    case Environment::ObjectType::NCAP_Child:
      return "NCAP_Child";
    case Environment::ObjectType::NCAP_Cyclist:
      return "NCAP_Cyclist";
    case Environment::ObjectType::NCAP_EBTA:
      return "NCAP_EBTA";
    case Environment::ObjectType::NCAP_GVT:
      return "NCAP_GVT";
    case Environment::ObjectType::NCAP_Motorcycle:
      return "NCAP_Motorcycle";
    case Environment::ObjectType::NCAP_Scooter:
      return "NCAP_Scooter";
    case Environment::ObjectType::NCAP_StreetLight:
      return "NCAP_StreetLight";
    case Environment::ObjectType::NL_Ambulance_Volvo_XC60:
      return "NL_Ambulance_Volvo_XC60";
    case Environment::ObjectType::Nissan_Ariya:
      return "Nissan_Ariya";
    case Environment::ObjectType::Nissan_Cabstar_Boxtruck:
      return "Nissan_Cabstar_Boxtruck";
    case Environment::ObjectType::OfficeBrownFlat:
      return "OfficeBrownFlat";
    case Environment::ObjectType::OfficeBrownTall1:
      return "OfficeBrownTall1";
    case Environment::ObjectType::OfficeBrownTall2:
      return "OfficeBrownTall2";
    case Environment::ObjectType::OfficeGreenTall:
      return "OfficeGreenTall";
    case Environment::ObjectType::Overhang1Light_JP:
      return "Overhang1Light_JP";
    case Environment::ObjectType::Overhang1Light_KR:
      return "Overhang1Light_KR";
    case Environment::ObjectType::Overhang1Light_NL:
      return "Overhang1Light_NL";
    case Environment::ObjectType::Overhang1Light_US:
      return "Overhang1Light_US";
    case Environment::ObjectType::Overhang1Post_JP:
      return "Overhang1Post_JP";
    case Environment::ObjectType::Overhang1Post_KR:
      return "Overhang1Post_KR";
    case Environment::ObjectType::Overhang1Post_NL:
      return "Overhang1Post_NL";
    case Environment::ObjectType::Overhang1Post_US:
      return "Overhang1Post_US";
    case Environment::ObjectType::Overhang2Lights_JP:
      return "Overhang2Lights_JP";
    case Environment::ObjectType::Overhang2Lights_KR:
      return "Overhang2Lights_KR";
    case Environment::ObjectType::Overhang2Lights_NL:
      return "Overhang2Lights_NL";
    case Environment::ObjectType::Overhang2Lights_US:
      return "Overhang2Lights_US";
    case Environment::ObjectType::Overhang2Post_JP:
      return "Overhang2Post_JP";
    case Environment::ObjectType::Overhang2Post_KR:
      return "Overhang2Post_KR";
    case Environment::ObjectType::Overhang2Post_NL:
      return "Overhang2Post_NL";
    case Environment::ObjectType::Overhang2Post_US:
      return "Overhang2Post_US";
    case Environment::ObjectType::OverhangDH2Lights_US:
      return "OverhangDH2Lights_US";
    case Environment::ObjectType::OverhangDHPost_US:
      return "OverhangDHPost_US";
    case Environment::ObjectType::Pallet:
      return "Pallet";
    case Environment::ObjectType::PedestrianSignal_JP:
      return "PedestrianSignal_JP";
    case Environment::ObjectType::Peterbilt_579:
      return "Peterbilt_579";
    case Environment::ObjectType::Peterbilt_579_Trailer:
      return "Peterbilt_579_Trailer";
    case Environment::ObjectType::PlasticBarrier100cm:
      return "PlasticBarrier100cm";
    case Environment::ObjectType::PrismSignV_30_50_70:
      return "PrismSignV_30_50_70";
    case Environment::ObjectType::PrismSignV_5_10_15:
      return "PrismSignV_5_10_15";
    case Environment::ObjectType::PrismSignV_80_100_110:
      return "PrismSignV_80_100_110";
    case Environment::ObjectType::PrismSign_30_50_70:
      return "PrismSign_30_50_70";
    case Environment::ObjectType::PrismSign_5_10_15:
      return "PrismSign_5_10_15";
    case Environment::ObjectType::PrismSign_80_100_110:
      return "PrismSign_80_100_110";
    case Environment::ObjectType::Pylon_01:
      return "Pylon_01";
    case Environment::ObjectType::Pylon_02:
      return "Pylon_02";
    case Environment::ObjectType::ReflectorSign:
      return "ReflectorSign";
    case Environment::ObjectType::ReflectorSignSimple:
      return "ReflectorSignSimple";
    case Environment::ObjectType::Rivian_R1T:
      return "Rivian_R1T";
    case Environment::ObjectType::Rivian_R1T_wCover:
      return "Rivian_R1T_wCover";
    case Environment::ObjectType::RoadClosed_wLights:
      return "RoadClosed_wLights";
    case Environment::ObjectType::RoadsideLight_NL:
      return "RoadsideLight_NL";
    case Environment::ObjectType::RoadsideMarker:
      return "RoadsideMarker";
    case Environment::ObjectType::RoadsidePost:
      return "RoadsidePost";
    case Environment::ObjectType::RoadsidePost_NL:
      return "RoadsidePost_NL";
    case Environment::ObjectType::Roewe_550_S_Sedan:
      return "Roewe_550_S_Sedan";
    case Environment::ObjectType::Row_Crop_Tractor:
      return "Row_Crop_Tractor";
    case Environment::ObjectType::School:
      return "School";
    case Environment::ObjectType::Scooter:
      return "Scooter";
    case Environment::ObjectType::Scooter_wBox:
      return "Scooter_wBox";
    case Environment::ObjectType::Serviceberry10y:
      return "Serviceberry10y";
    case Environment::ObjectType::Serviceberry15y:
      return "Serviceberry15y";
    case Environment::ObjectType::Serviceberry5y:
      return "Serviceberry5y";
    case Environment::ObjectType::ShoppingCart:
      return "ShoppingCart";
    case Environment::ObjectType::Siemens_eRod:
      return "Siemens_eRod";
    case Environment::ObjectType::SignalCasing20cm_NL:
      return "SignalCasing20cm_NL";
    case Environment::ObjectType::SignalCasing30cmDH_US:
      return "SignalCasing30cmDH_US";
    case Environment::ObjectType::SignalCasing30cm_JP:
      return "SignalCasing30cm_JP";
    case Environment::ObjectType::SignalCasing30cm_NL:
      return "SignalCasing30cm_NL";
    case Environment::ObjectType::SignalCasing30cm_US:
      return "SignalCasing30cm_US";
    case Environment::ObjectType::SignalCasing3_30cm_KR:
      return "SignalCasing3_30cm_KR";
    case Environment::ObjectType::SignalCasing4_30cm_KR:
      return "SignalCasing4_30cm_KR";
    case Environment::ObjectType::Skywell:
      return "Skywell";
    case Environment::ObjectType::SpeedBump250cm:
      return "SpeedBump250cm";
    case Environment::ObjectType::SpeedBump350cm:
      return "SpeedBump350cm";
    case Environment::ObjectType::Sports_Bike:
      return "Sports_Bike";
    case Environment::ObjectType::Sports_Bike_wDriver:
      return "Sports_Bike_wDriver";
    case Environment::ObjectType::SpringPost46cm:
      return "SpringPost46cm";
    case Environment::ObjectType::SpringPost75cm:
      return "SpringPost75cm";
    case Environment::ObjectType::SpringPost95cm:
      return "SpringPost95cm";
    case Environment::ObjectType::Suzuki_Hustler_Hybrid:
      return "Suzuki_Hustler_Hybrid";
    case Environment::ObjectType::TerracedHouses:
      return "TerracedHouses";
    case Environment::ObjectType::Tesla_Model_3:
      return "Tesla_Model_3";
    case Environment::ObjectType::Tire_Horizontal:
      return "Tire_Horizontal";
    case Environment::ObjectType::Tire_Vertical:
      return "Tire_Vertical";
    case Environment::ObjectType::Toddler_050:
      return "Toddler_050";
    case Environment::ObjectType::Toyota_Previa_MPV:
      return "Toyota_Previa_MPV";
    case Environment::ObjectType::Toyota_Prius_Sedan:
      return "Toyota_Prius_Sedan";
    case Environment::ObjectType::Toyota_Yaris_Hatchback:
      return "Toyota_Yaris_Hatchback";
    case Environment::ObjectType::TrashBin_240L:
      return "TrashBin_240L";
    case Environment::ObjectType::TrashCan_Rnd_130L:
      return "TrashCan_Rnd_130L";
    case Environment::ObjectType::TrashCan_Sqr_160L:
      return "TrashCan_Sqr_160L";
    case Environment::ObjectType::TriangleParkingSpaceLock:
      return "TriangleParkingSpaceLock";
    case Environment::ObjectType::TurkishHazel10y:
      return "TurkishHazel10y";
    case Environment::ObjectType::TurkishHazel20y:
      return "TurkishHazel20y";
    case Environment::ObjectType::US_Police_Volvo_XC60:
      return "US_Police_Volvo_XC60";
    case Environment::ObjectType::VehicleSignal30cm_FL_JP:
      return "VehicleSignal30cm_FL_JP";
    case Environment::ObjectType::VehicleSignal30cm_FR_JP:
      return "VehicleSignal30cm_FR_JP";
    case Environment::ObjectType::VehicleSignal30cm_F_JP:
      return "VehicleSignal30cm_F_JP";
    case Environment::ObjectType::VehicleSignal30cm_L_JP:
      return "VehicleSignal30cm_L_JP";
    case Environment::ObjectType::VehicleSignal30cm_R_JP:
      return "VehicleSignal30cm_R_JP";
    case Environment::ObjectType::VehicleSignalGreen30cm_JP:
      return "VehicleSignalGreen30cm_JP";
    case Environment::ObjectType::VehicleSignalOrange30cm_JP:
      return "VehicleSignalOrange30cm_JP";
    case Environment::ObjectType::VehicleSignalRed30cm_JP:
      return "VehicleSignalRed30cm_JP";
    case Environment::ObjectType::Volvo_FH16:
      return "Volvo_FH16";
    case Environment::ObjectType::Volvo_XC60:
      return "Volvo_XC60";
    case Environment::ObjectType::Warehouse:
      return "Warehouse";
    case Environment::ObjectType::Wheat_A:
      return "Wheat_A";
    case Environment::ObjectType::Wheat_B:
      return "Wheat_B";
    case Environment::ObjectType::Wheat_C:
      return "Wheat_C";
    case Environment::ObjectType::WheelieBin_1100L:
      return "WheelieBin_1100L";
    case Environment::ObjectType::Windmill:
      return "Windmill";
    case Environment::ObjectType::Wuling_Hongguang:
      return "Wuling_Hongguang";
    case Environment::ObjectType::Church:
      return "Church";
    case Environment::ObjectType::Factory:
      return "Factory";
    case Environment::ObjectType::ConcreteGuardrail:
      return "ConcreteGuardrail";
    case Environment::ObjectType::Guardrail:
      return "Guardrail";
    case Environment::ObjectType::Fence:
      return "Fence";
    case Environment::ObjectType::LinePlacedRoadImperfection:
      return "LinePlacedRoadImperfection";
    case Environment::ObjectType::SoundAbsorbingWall:
      return "SoundAbsorbingWall";
    case Environment::ObjectType::Wall:
      return "Wall";
    case Environment::ObjectType::House:
      return "House";
    case Environment::ObjectType::Office:
      return "Office";
    case Environment::ObjectType::Box:
      return "Box";
    case Environment::ObjectType::Capsule:
      return "Capsule";
    case Environment::ObjectType::Cone:
      return "Cone";
    case Environment::ObjectType::Cylinder:
      return "Cylinder";
    case Environment::ObjectType::Sphere:
      return "Sphere";
    case Environment::ObjectType::Tripod:
      return "Tripod";
    case Environment::ObjectType::TrafficSignPole:
      return "TrafficSignPole";
    default:
      SYMAWARE_UNREACHABLE();
  }
}

}  // namespace symaware