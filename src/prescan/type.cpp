#include "symaware/prescan/type.h"

#include "symaware/util/exception.h"

namespace symaware {

std::string to_string(const Gear gear) {
  switch (gear) {
    case Gear::Forward:
      return "Forward";
    case Gear::Neutral:
      return "Neutral";
    case Gear::Reverse:
      return "Reverse";
    case Gear::Undefined:
      return "Undefined";
    default:
      return "Unknown";
  }
}
std::string to_string(const SensorType sensor_type) {
  switch (sensor_type) {
    case SensorType::AIR:
      return "AIR";
    case SensorType::ALMS:
      return "ALMS";
    case SensorType::BRS:
      return "BRS";
    case SensorType::CAMERA:
      return "CAMERA";
    case SensorType::IR_BEACON:
      return "IR_BEACON";
    case SensorType::IR_OBU:
      return "IR_OBU";
    case SensorType::RF_BEACON:
      return "RF_BEACON";
    case SensorType::RF_OBU:
      return "RF_OBU";
    case SensorType::DEPTH_CAMERA:
      return "DEPTH_CAMERA";
    case SensorType::ISS:
      return "ISS";
    case SensorType::LIDA:
      return "LIDA";
    case SensorType::LMS:
      return "LMS";
    case SensorType::OCS:
      return "OCS";
    case SensorType::PCS:
      return "PCS";
    case SensorType::PHYSICS_BASED_CAMERA_UNREAL:
      return "PHYSICS_BASED_CAMERA_UNREAL";
    case SensorType::RADAR:
      return "RADAR";
    case SensorType::TIS:
      return "TIS";
    case SensorType::TRAFFIC_SIGNAL:
      return "TRAFFIC_SIGNAL";
    case SensorType::ULTRASONIC:
      return "ULTRASONIC";
    case SensorType::WORLD_VIEWER:
      return "WORLD_VIEWER";
    default:
      SYMAWARE_UNREACHABLE();
  }
}
std::string to_string(const WeatherType weather_type) {
  switch (weather_type) {
    case WeatherType::SUNNY:
      return "Sunny";
    case WeatherType::RAINY:
      return "Rainy";
    case WeatherType::SNOWY:
      return "Snowy";
    default:
      SYMAWARE_UNREACHABLE();
  }
}
std::string to_string(const SkyType sky_type) {
  switch (sky_type) {
    case SkyType::DAWN:
      return "Dawn";
    case SkyType::DAY:
      return "Day";
    case SkyType::DUSK:
      return "Dusk";
    case SkyType::NIGHT:
      return "Night";
    default:
      SYMAWARE_UNREACHABLE();
  }
}
std::string to_string(const ObjectType object_type) {
  switch (object_type) {
    case ObjectType::ADAC_target_yellow_merc:
      return "ADAC_target_yellow_merc";
    case ObjectType::ApartmentBuilding:
      return "ApartmentBuilding";
    case ObjectType::ArrowBoard_Trailer:
      return "ArrowBoard_Trailer";
    case ObjectType::Ash10y:
      return "Ash10y";
    case ObjectType::Ash20y:
      return "Ash20y";
    case ObjectType::Audi_A3:
      return "Audi_A3";
    case ObjectType::Audi_A8_Sedan:
      return "Audi_A8_Sedan";
    case ObjectType::AustrianPine10y:
      return "AustrianPine10y";
    case ObjectType::AustrianPine20y:
      return "AustrianPine20y";
    case ObjectType::BE_Police_Volvo_XC60:
      return "BE_Police_Volvo_XC60";
    case ObjectType::BMW_X5_SUV:
      return "BMW_X5_SUV";
    case ObjectType::BMW_Z3_Convertible:
      return "BMW_Z3_Convertible";
    case ObjectType::BalloonCar:
      return "BalloonCar";
    case ObjectType::BarrierFence:
      return "BarrierFence";
    case ObjectType::Birch10y:
      return "Birch10y";
    case ObjectType::Birch20y:
      return "Birch20y";
    case ObjectType::BlueSpruce10y:
      return "BlueSpruce10y";
    case ObjectType::BlueSpruce20y:
      return "BlueSpruce20y";
    case ObjectType::BottsDots_White:
      return "BottsDots_White";
    case ObjectType::BottsDots_Yellow:
      return "BottsDots_Yellow";
    case ObjectType::Boy_100:
      return "Boy_100";
    case ObjectType::Boy_150:
      return "Boy_150";
    case ObjectType::Building_00A:
      return "Building_00A";
    case ObjectType::Building_01A:
      return "Building_01A";
    case ObjectType::Building_02A:
      return "Building_02A";
    case ObjectType::Building_03A:
      return "Building_03A";
    case ObjectType::Building_04A:
      return "Building_04A";
    case ObjectType::Building_05A:
      return "Building_05A";
    case ObjectType::Building_06A:
      return "Building_06A";
    case ObjectType::Building_07A:
      return "Building_07A";
    case ObjectType::Building_08A:
      return "Building_08A";
    case ObjectType::Busstop:
      return "Busstop";
    case ObjectType::CAT_725:
      return "CAT_725";
    case ObjectType::Cadillac_Escalade:
      return "Cadillac_Escalade";
    case ObjectType::CarDealer:
      return "CarDealer";
    case ObjectType::Car_Trailer_Small:
      return "Car_Trailer_Small";
    case ObjectType::CatsEyesR:
      return "CatsEyesR";
    case ObjectType::CatsEyesW:
      return "CatsEyesW";
    case ObjectType::CatsEyesWR:
      return "CatsEyesWR";
    case ObjectType::CatsEyesWY:
      return "CatsEyesWY";
    case ObjectType::CatsEyesY:
      return "CatsEyesY";
    case ObjectType::Child_Leaning:
      return "Child_Leaning";
    case ObjectType::Child_Overweight:
      return "Child_Overweight";
    case ObjectType::Child_Regular:
      return "Child_Regular";
    case ObjectType::Child_Sitting:
      return "Child_Sitting";
    case ObjectType::CinderBlock_A:
      return "CinderBlock_A";
    case ObjectType::CinderBlock_B:
      return "CinderBlock_B";
    case ObjectType::CinderBlock_C:
      return "CinderBlock_C";
    case ObjectType::Citroen_C3_Hatchback:
      return "Citroen_C3_Hatchback";
    case ObjectType::ConstructionSign_JP:
      return "ConstructionSign_JP";
    case ObjectType::Container_Trailer:
      return "Container_Trailer";
    case ObjectType::CornerReflector138mm:
      return "CornerReflector138mm";
    case ObjectType::CornerReflector176_8mm:
      return "CornerReflector176_8mm";
    case ObjectType::CornerReflector46_35mm:
      return "CornerReflector46_35mm";
    case ObjectType::Cotton_A:
      return "Cotton_A";
    case ObjectType::Cotton_B:
      return "Cotton_B";
    case ObjectType::Cotton_C:
      return "Cotton_C";
    case ObjectType::DAF_95_XF:
      return "DAF_95_XF";
    case ObjectType::DAF_Euro_6_XF:
      return "DAF_Euro_6_XF";
    case ObjectType::Deer:
      return "Deer";
    case ObjectType::Dogwood10y:
      return "Dogwood10y";
    case ObjectType::Dogwood20y:
      return "Dogwood20y";
    case ObjectType::Dumpster_2300L:
      return "Dumpster_2300L";
    case ObjectType::DutchChurch:
      return "DutchChurch";
    case ObjectType::Empty_Light_Node:
      return "Empty_Light_Node";
    case ObjectType::Existing:
      return "Existing";
    case ObjectType::FAW_Jiefang_J6M:
      return "FAW_Jiefang_J6M";
    case ObjectType::FShape150cm:
      return "FShape150cm";
    case ObjectType::FShape250cm:
      return "FShape250cm";
    case ObjectType::FShape350cm:
      return "FShape350cm";
    case ObjectType::Female_Bending:
      return "Female_Bending";
    case ObjectType::Female_Leaning:
      return "Female_Leaning";
    case ObjectType::Female_Overweight:
      return "Female_Overweight";
    case ObjectType::Female_Regular:
      return "Female_Regular";
    case ObjectType::Female_wBuggy:
      return "Female_wBuggy";
    case ObjectType::Female_wLongCoat:
      return "Female_wLongCoat";
    case ObjectType::Female_wRaincoat:
      return "Female_wRaincoat";
    case ObjectType::Female_wShoppingCart:
      return "Female_wShoppingCart";
    case ObjectType::Fiat_Bravo_Hatchback:
      return "Fiat_Bravo_Hatchback";
    case ObjectType::FireBrigade:
      return "FireBrigade";
    case ObjectType::Ford_Fiesta_Hatchback:
      return "Ford_Fiesta_Hatchback";
    case ObjectType::Ford_Focus_Stationwagon:
      return "Ford_Focus_Stationwagon";
    case ObjectType::Full_Trailer:
      return "Full_Trailer";
    case ObjectType::Garage_Ground_Floor:
      return "Garage_Ground_Floor";
    case ObjectType::Garage_Mid_Floor:
      return "Garage_Mid_Floor";
    case ObjectType::Garage_Top_Floor:
      return "Garage_Top_Floor";
    case ObjectType::GasStation:
      return "GasStation";
    case ObjectType::Genesis_GV80:
      return "Genesis_GV80";
    case ObjectType::GuardrailReflector_RectR:
      return "GuardrailReflector_RectR";
    case ObjectType::GuardrailReflector_RectW:
      return "GuardrailReflector_RectW";
    case ObjectType::GuardrailReflector_RectWR:
      return "GuardrailReflector_RectWR";
    case ObjectType::GuardrailReflector_RoundR:
      return "GuardrailReflector_RoundR";
    case ObjectType::GuardrailReflector_RoundW:
      return "GuardrailReflector_RoundW";
    case ObjectType::GuardrailReflector_RoundWR:
      return "GuardrailReflector_RoundWR";
    case ObjectType::GuardrailReflector_RoundY:
      return "GuardrailReflector_RoundY";
    case ObjectType::GuidedSoftTarget:
      return "GuidedSoftTarget";
    case ObjectType::HOWO_T5G_Cement_Truck:
      return "HOWO_T5G_Cement_Truck";
    case ObjectType::Hino_Blue_Ribbon:
      return "Hino_Blue_Ribbon";
    case ObjectType::Honda_Pan_European_Motorcycle:
      return "Honda_Pan_European_Motorcycle";
    case ObjectType::Honda_Pan_European_Motorcycle_With_Driver:
      return "Honda_Pan_European_Motorcycle_With_Driver";
    case ObjectType::HouseModern:
      return "HouseModern";
    case ObjectType::HouseOld1:
      return "HouseOld1";
    case ObjectType::HouseOld2:
      return "HouseOld2";
    case ObjectType::HouseOld3:
      return "HouseOld3";
    case ObjectType::HouseOld4:
      return "HouseOld4";
    case ObjectType::HouseOld5:
      return "HouseOld5";
    case ObjectType::HouseOld6:
      return "HouseOld6";
    case ObjectType::Houses1930s:
      return "Houses1930s";
    case ObjectType::Hyundai_Ioniq5:
      return "Hyundai_Ioniq5";
    case ObjectType::Hyundai_i30_NLine:
      return "Hyundai_i30_NLine";
    case ObjectType::Isuzu_DMax:
      return "Isuzu_DMax";
    case ObjectType::Isuzu_Giga_Fire_Truck:
      return "Isuzu_Giga_Fire_Truck";
    case ObjectType::JAC_HFC_Series:
      return "JAC_HFC_Series";
    case ObjectType::JapaneseMaple10y:
      return "JapaneseMaple10y";
    case ObjectType::JapaneseMaple20y:
      return "JapaneseMaple20y";
    case ObjectType::Joby_Aviation_S4:
      return "Joby_Aviation_S4";
    case ObjectType::Kia_EV6:
      return "Kia_EV6";
    case ObjectType::Kia_EV6_wRoofRack:
      return "Kia_EV6_wRoofRack";
    case ObjectType::Kia_EV6_wRoofRack_Siemens:
      return "Kia_EV6_wRoofRack_Siemens";
    case ObjectType::Lexus_GS_450h_F_Sport_Sedan:
      return "Lexus_GS_450h_F_Sport_Sedan";
    case ObjectType::Lexus_LS_600h_F_Sport:
      return "Lexus_LS_600h_F_Sport";
    case ObjectType::LightPost:
      return "LightPost";
    case ObjectType::Lilac10y:
      return "Lilac10y";
    case ObjectType::Lilac20y:
      return "Lilac20y";
    case ObjectType::Magnolia10y:
      return "Magnolia10y";
    case ObjectType::Magnolia20y:
      return "Magnolia20y";
    case ObjectType::Male_200:
      return "Male_200";
    case ObjectType::Male_African:
      return "Male_African";
    case ObjectType::Male_Bending:
      return "Male_Bending";
    case ObjectType::Male_BendingOver:
      return "Male_BendingOver";
    case ObjectType::Male_CyclingCyclist:
      return "Male_CyclingCyclist";
    case ObjectType::Male_Female_HandInHand:
      return "Male_Female_HandInHand";
    case ObjectType::Male_LargeShoulderSuitcase:
      return "Male_LargeShoulderSuitcase";
    case ObjectType::Male_Leaning:
      return "Male_Leaning";
    case ObjectType::Male_LeaningBack:
      return "Male_LeaningBack";
    case ObjectType::Male_LyingDown:
      return "Male_LyingDown";
    case ObjectType::Male_Old_White_WithStick:
      return "Male_Old_White_WithStick";
    case ObjectType::Male_Old_White_WithWalker:
      return "Male_Old_White_WithWalker";
    case ObjectType::Male_Old_White_WithWalkerWithWheels:
      return "Male_Old_White_WithWalkerWithWheels";
    case ObjectType::Male_Overweight:
      return "Male_Overweight";
    case ObjectType::Male_Regular:
      return "Male_Regular";
    case ObjectType::Male_ShoppingBag:
      return "Male_ShoppingBag";
    case ObjectType::Male_Sitting:
      return "Male_Sitting";
    case ObjectType::Male_wBackpack:
      return "Male_wBackpack";
    case ObjectType::Male_wBicycle:
      return "Male_wBicycle";
    case ObjectType::Male_wLargeBackpack:
      return "Male_wLargeBackpack";
    case ObjectType::Male_wLongCoat:
      return "Male_wLongCoat";
    case ObjectType::Male_wRaincoat:
      return "Male_wRaincoat";
    case ObjectType::Male_wSuit:
      return "Male_wSuit";
    case ObjectType::Male_wSuitcase:
      return "Male_wSuitcase";
    case ObjectType::Man_250:
      return "Man_250";
    case ObjectType::Man_Asian:
      return "Man_Asian";
    case ObjectType::Mazda_RX8_Coupe:
      return "Mazda_RX8_Coupe";
    case ObjectType::MercedesBenz_Actros_1851_LS_4x2:
      return "MercedesBenz_Actros_1851_LS_4x2";
    case ObjectType::MercedesBenz_Actros_1860_LS_4x2:
      return "MercedesBenz_Actros_1860_LS_4x2";
    case ObjectType::MercedesBenz_Actros_2541_L_6x2:
      return "MercedesBenz_Actros_2541_L_6x2";
    case ObjectType::Mitsubishi_Outlander_PHEV:
      return "Mitsubishi_Outlander_PHEV";
    case ObjectType::Monument:
      return "Monument";
    case ObjectType::NCAP_Adult:
      return "NCAP_Adult";
    case ObjectType::NCAP_Child:
      return "NCAP_Child";
    case ObjectType::NCAP_Cyclist:
      return "NCAP_Cyclist";
    case ObjectType::NCAP_EBTA:
      return "NCAP_EBTA";
    case ObjectType::NCAP_GVT:
      return "NCAP_GVT";
    case ObjectType::NCAP_Motorcycle:
      return "NCAP_Motorcycle";
    case ObjectType::NCAP_Scooter:
      return "NCAP_Scooter";
    case ObjectType::NCAP_StreetLight:
      return "NCAP_StreetLight";
    case ObjectType::NL_Ambulance_Volvo_XC60:
      return "NL_Ambulance_Volvo_XC60";
    case ObjectType::Nissan_Ariya:
      return "Nissan_Ariya";
    case ObjectType::Nissan_Cabstar_Boxtruck:
      return "Nissan_Cabstar_Boxtruck";
    case ObjectType::OfficeBrownFlat:
      return "OfficeBrownFlat";
    case ObjectType::OfficeBrownTall1:
      return "OfficeBrownTall1";
    case ObjectType::OfficeBrownTall2:
      return "OfficeBrownTall2";
    case ObjectType::OfficeGreenTall:
      return "OfficeGreenTall";
    case ObjectType::Overhang1Light_JP:
      return "Overhang1Light_JP";
    case ObjectType::Overhang1Light_KR:
      return "Overhang1Light_KR";
    case ObjectType::Overhang1Light_NL:
      return "Overhang1Light_NL";
    case ObjectType::Overhang1Light_US:
      return "Overhang1Light_US";
    case ObjectType::Overhang1Post_JP:
      return "Overhang1Post_JP";
    case ObjectType::Overhang1Post_KR:
      return "Overhang1Post_KR";
    case ObjectType::Overhang1Post_NL:
      return "Overhang1Post_NL";
    case ObjectType::Overhang1Post_US:
      return "Overhang1Post_US";
    case ObjectType::Overhang2Lights_JP:
      return "Overhang2Lights_JP";
    case ObjectType::Overhang2Lights_KR:
      return "Overhang2Lights_KR";
    case ObjectType::Overhang2Lights_NL:
      return "Overhang2Lights_NL";
    case ObjectType::Overhang2Lights_US:
      return "Overhang2Lights_US";
    case ObjectType::Overhang2Post_JP:
      return "Overhang2Post_JP";
    case ObjectType::Overhang2Post_KR:
      return "Overhang2Post_KR";
    case ObjectType::Overhang2Post_NL:
      return "Overhang2Post_NL";
    case ObjectType::Overhang2Post_US:
      return "Overhang2Post_US";
    case ObjectType::OverhangDH2Lights_US:
      return "OverhangDH2Lights_US";
    case ObjectType::OverhangDHPost_US:
      return "OverhangDHPost_US";
    case ObjectType::Pallet:
      return "Pallet";
    case ObjectType::PedestrianSignal_JP:
      return "PedestrianSignal_JP";
    case ObjectType::Peterbilt_579:
      return "Peterbilt_579";
    case ObjectType::Peterbilt_579_Trailer:
      return "Peterbilt_579_Trailer";
    case ObjectType::PlasticBarrier100cm:
      return "PlasticBarrier100cm";
    case ObjectType::PrismSignV_30_50_70:
      return "PrismSignV_30_50_70";
    case ObjectType::PrismSignV_5_10_15:
      return "PrismSignV_5_10_15";
    case ObjectType::PrismSignV_80_100_110:
      return "PrismSignV_80_100_110";
    case ObjectType::PrismSign_30_50_70:
      return "PrismSign_30_50_70";
    case ObjectType::PrismSign_5_10_15:
      return "PrismSign_5_10_15";
    case ObjectType::PrismSign_80_100_110:
      return "PrismSign_80_100_110";
    case ObjectType::Pylon_01:
      return "Pylon_01";
    case ObjectType::Pylon_02:
      return "Pylon_02";
    case ObjectType::ReflectorSign:
      return "ReflectorSign";
    case ObjectType::ReflectorSignSimple:
      return "ReflectorSignSimple";
    case ObjectType::Rivian_R1T:
      return "Rivian_R1T";
    case ObjectType::Rivian_R1T_wCover:
      return "Rivian_R1T_wCover";
    case ObjectType::RoadClosed_wLights:
      return "RoadClosed_wLights";
    case ObjectType::RoadsideLight_NL:
      return "RoadsideLight_NL";
    case ObjectType::RoadsideMarker:
      return "RoadsideMarker";
    case ObjectType::RoadsidePost:
      return "RoadsidePost";
    case ObjectType::RoadsidePost_NL:
      return "RoadsidePost_NL";
    case ObjectType::Roewe_550_S_Sedan:
      return "Roewe_550_S_Sedan";
    case ObjectType::Row_Crop_Tractor:
      return "Row_Crop_Tractor";
    case ObjectType::School:
      return "School";
    case ObjectType::Scooter:
      return "Scooter";
    case ObjectType::Scooter_wBox:
      return "Scooter_wBox";
    case ObjectType::Serviceberry10y:
      return "Serviceberry10y";
    case ObjectType::Serviceberry15y:
      return "Serviceberry15y";
    case ObjectType::Serviceberry5y:
      return "Serviceberry5y";
    case ObjectType::ShoppingCart:
      return "ShoppingCart";
    case ObjectType::Siemens_eRod:
      return "Siemens_eRod";
    case ObjectType::SignalCasing20cm_NL:
      return "SignalCasing20cm_NL";
    case ObjectType::SignalCasing30cmDH_US:
      return "SignalCasing30cmDH_US";
    case ObjectType::SignalCasing30cm_JP:
      return "SignalCasing30cm_JP";
    case ObjectType::SignalCasing30cm_NL:
      return "SignalCasing30cm_NL";
    case ObjectType::SignalCasing30cm_US:
      return "SignalCasing30cm_US";
    case ObjectType::SignalCasing3_30cm_KR:
      return "SignalCasing3_30cm_KR";
    case ObjectType::SignalCasing4_30cm_KR:
      return "SignalCasing4_30cm_KR";
    case ObjectType::Skywell:
      return "Skywell";
    case ObjectType::SpeedBump250cm:
      return "SpeedBump250cm";
    case ObjectType::SpeedBump350cm:
      return "SpeedBump350cm";
    case ObjectType::Sports_Bike:
      return "Sports_Bike";
    case ObjectType::Sports_Bike_wDriver:
      return "Sports_Bike_wDriver";
    case ObjectType::SpringPost46cm:
      return "SpringPost46cm";
    case ObjectType::SpringPost75cm:
      return "SpringPost75cm";
    case ObjectType::SpringPost95cm:
      return "SpringPost95cm";
    case ObjectType::Suzuki_Hustler_Hybrid:
      return "Suzuki_Hustler_Hybrid";
    case ObjectType::TerracedHouses:
      return "TerracedHouses";
    case ObjectType::Tesla_Model_3:
      return "Tesla_Model_3";
    case ObjectType::Tire_Horizontal:
      return "Tire_Horizontal";
    case ObjectType::Tire_Vertical:
      return "Tire_Vertical";
    case ObjectType::Toddler_050:
      return "Toddler_050";
    case ObjectType::Toyota_Previa_MPV:
      return "Toyota_Previa_MPV";
    case ObjectType::Toyota_Prius_Sedan:
      return "Toyota_Prius_Sedan";
    case ObjectType::Toyota_Yaris_Hatchback:
      return "Toyota_Yaris_Hatchback";
    case ObjectType::TrashBin_240L:
      return "TrashBin_240L";
    case ObjectType::TrashCan_Rnd_130L:
      return "TrashCan_Rnd_130L";
    case ObjectType::TrashCan_Sqr_160L:
      return "TrashCan_Sqr_160L";
    case ObjectType::TriangleParkingSpaceLock:
      return "TriangleParkingSpaceLock";
    case ObjectType::TurkishHazel10y:
      return "TurkishHazel10y";
    case ObjectType::TurkishHazel20y:
      return "TurkishHazel20y";
    case ObjectType::US_Police_Volvo_XC60:
      return "US_Police_Volvo_XC60";
    case ObjectType::VehicleSignal30cm_FL_JP:
      return "VehicleSignal30cm_FL_JP";
    case ObjectType::VehicleSignal30cm_FR_JP:
      return "VehicleSignal30cm_FR_JP";
    case ObjectType::VehicleSignal30cm_F_JP:
      return "VehicleSignal30cm_F_JP";
    case ObjectType::VehicleSignal30cm_L_JP:
      return "VehicleSignal30cm_L_JP";
    case ObjectType::VehicleSignal30cm_R_JP:
      return "VehicleSignal30cm_R_JP";
    case ObjectType::VehicleSignalGreen30cm_JP:
      return "VehicleSignalGreen30cm_JP";
    case ObjectType::VehicleSignalOrange30cm_JP:
      return "VehicleSignalOrange30cm_JP";
    case ObjectType::VehicleSignalRed30cm_JP:
      return "VehicleSignalRed30cm_JP";
    case ObjectType::Volvo_FH16:
      return "Volvo_FH16";
    case ObjectType::Volvo_XC60:
      return "Volvo_XC60";
    case ObjectType::Warehouse:
      return "Warehouse";
    case ObjectType::Wheat_A:
      return "Wheat_A";
    case ObjectType::Wheat_B:
      return "Wheat_B";
    case ObjectType::Wheat_C:
      return "Wheat_C";
    case ObjectType::WheelieBin_1100L:
      return "WheelieBin_1100L";
    case ObjectType::Windmill:
      return "Windmill";
    case ObjectType::Wuling_Hongguang:
      return "Wuling_Hongguang";
    case ObjectType::Church:
      return "Church";
    case ObjectType::Factory:
      return "Factory";
    case ObjectType::ConcreteGuardrail:
      return "ConcreteGuardrail";
    case ObjectType::Guardrail:
      return "Guardrail";
    case ObjectType::Fence:
      return "Fence";
    case ObjectType::LinePlacedRoadImperfection:
      return "LinePlacedRoadImperfection";
    case ObjectType::SoundAbsorbingWall:
      return "SoundAbsorbingWall";
    case ObjectType::Wall:
      return "Wall";
    case ObjectType::House:
      return "House";
    case ObjectType::Office:
      return "Office";
    case ObjectType::Box:
      return "Box";
    case ObjectType::Capsule:
      return "Capsule";
    case ObjectType::Cone:
      return "Cone";
    case ObjectType::Cylinder:
      return "Cylinder";
    case ObjectType::Sphere:
      return "Sphere";
    case ObjectType::Tripod:
      return "Tripod";
    case ObjectType::TrafficSignPole:
      return "TrafficSignPole";
    default:
      SYMAWARE_UNREACHABLE();
  }
}

std::ostream& operator<<(std::ostream& os, const Gear gear) { return os << to_string(gear); }
std::ostream& operator<<(std::ostream& os, const SensorType sensor_type) { return os << to_string(sensor_type); }
std::ostream& operator<<(std::ostream& os, const WeatherType weather_type) { return os << to_string(weather_type); }
std::ostream& operator<<(std::ostream& os, const SkyType sky_type) { return os << to_string(sky_type); }
std::ostream& operator<<(std::ostream& os, const ObjectType object_type) { return os << to_string(object_type); }

}  // namespace symaware
