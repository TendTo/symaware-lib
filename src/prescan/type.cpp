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

std::ostream& operator<<(std::ostream& os, const Gear gear) { return os << to_string(gear); }
std::ostream& operator<<(std::ostream& os, const SensorType sensor_type) { return os << to_string(sensor_type); }

}  // namespace symaware
