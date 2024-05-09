#include "symaware/prescan/type.h"
#include "symaware_prescan.h"

namespace py = pybind11;

void init_type(py::module_ &m) {
  py::enum_<symaware::Gear>(m, "Gear")
      .value("Forward", symaware::Gear::Forward, "Forward gear")
      .value("Neutral", symaware::Gear::Neutral, "Neutral gear")
      .value("Reverse", symaware::Gear::Reverse, "Reverse gear")
      .value("Undefined", symaware::Gear::Undefined, "Undefined gear. Won't change the gear.")
      .export_values();
  py::enum_<symaware::SensorType>(m, "SensorType")
      .value("AIR", symaware::SensorType::AIR)
      .value("ALMS", symaware::SensorType::ALMS)
      .value("BRS", symaware::SensorType::BRS)
      .value("CAMERA", symaware::SensorType::CAMERA)
      .value("IR_BEACON", symaware::SensorType::IR_BEACON)
      .value("IR_OBU", symaware::SensorType::IR_OBU)
      .value("RF_BEACON", symaware::SensorType::RF_BEACON)
      .value("RF_OBU", symaware::SensorType::RF_OBU)
      .value("DEPTH_CAMERA", symaware::SensorType::DEPTH_CAMERA)
      .value("ISS", symaware::SensorType::ISS)
      .value("LIDA", symaware::SensorType::LIDA)
      .value("LMS", symaware::SensorType::LMS)
      .value("OCS", symaware::SensorType::OCS)
      .value("PCS", symaware::SensorType::PCS)
      .value("PHYSICS_BASED_CAMERA_UNREAL", symaware::SensorType::PHYSICS_BASED_CAMERA_UNREAL)
      .value("RADAR", symaware::SensorType::RADAR)
      .value("TIS", symaware::SensorType::TIS)
      .value("TRAFFIC_SIGNAL", symaware::SensorType::TRAFFIC_SIGNAL)
      .value("ULTRASONIC", symaware::SensorType::ULTRASONIC)
      .value("WORLD_VIEWER", symaware::SensorType::WORLD_VIEWER);
}
