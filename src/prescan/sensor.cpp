#include "symaware/prescan/sensor.h"

#include <prescan/api/Air.hpp>
#include <prescan/api/Brs.hpp>
#include <prescan/api/Camera.hpp>
#include <prescan/api/Experiment.hpp>
#include <prescan/api/Lms.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/AirSensorUnit.hpp>
#include <prescan/sim/BrsSensorUnit.hpp>
#include <prescan/sim/CameraSensorUnit.hpp>
#include <prescan/sim/LmsSensorUnit.hpp>
#include <prescan/sim/SelfSensorUnit.hpp>

#include "symaware/util/exception.h"

#define CREATE_SENSOR(namespace, sensor_type, object)              \
  std::make_unique<prescan::api::namespace ::sensor_type##Sensor>( \
      prescan::api::namespace ::create##sensor_type##Sensor(object))

#define GET_ATTACHED_SENSOR(namespace, sensor_type, object, id)    \
  std::make_unique<prescan::api::namespace ::sensor_type##Sensor>( \
      prescan::api::namespace ::getAttached##sensor_type##Sensors(object).at(id))

#define INITIALISE_SENSOR(existing, namespace, sensor_type, object, id) \
  existing ? CREATE_SENSOR(namespace, sensor_type, object) : GET_ATTACHED_SENSOR(namespace, sensor_type, object, id)

#define REGISTER_SENSOR_UNIT(namespace, sensor_type, object, id)                                              \
  sensor_unit_ =                                                                                              \
      std::make_unique<prescan::sim::Unit>(prescan::sim::registerUnit<prescan::sim::sensor_type##SensorUnit>( \
          simulation, prescan::api::namespace ::getAttached##sensor_type##Sensors(object).at(id)));

#define REGISTER_SENSOR_UNIT_ARGS(namespace, sensor_type, object, id, ...)                                    \
  sensor_unit_ =                                                                                              \
      std::make_unique<prescan::sim::Unit>(prescan::sim::registerUnit<prescan::sim::sensor_type##SensorUnit>( \
          simulation, prescan::api::namespace ::getAttached##sensor_type##Sensors(object).at(id), __VA_ARGS__));

namespace symaware {

namespace {
template <class T>
inline T double_to_enum(const double value) {
  return static_cast<T>(static_cast<int>(value));
}

}  // namespace

Sensor::Sensor(const SensorType sensor_type, const bool existing) : Sensor{sensor_type, {}, existing} {}
Sensor::Sensor(const SensorType sensor_type, std::vector<double> setup, const bool existing)
    : existing_{existing},
      id_{-1},
      sensor_type_{sensor_type},
      setup_{std::move(setup)},
      image_{nullptr, 0, 0, prescan::api::camera::ImageFormat::CameraSensorImageFormatBGRU8},
      sensor_unit_{nullptr} {
  switch (sensor_type_) {
    case SensorType::AIR:
    case SensorType::BRS:
    case SensorType::CAMERA:
    case SensorType::LMS:
      break;
    default:
      SYMAWARE_RUNTIME_ERROR_FMT("Sensor {} not yet implemented", sensor_type_);
  }
}

template <>
inline void Sensor::applySetup(prescan::api::air::AirSensor* const sensor) {
  if (setup_.size() != 10)
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: 10 != {}", sensor_type_, setup_.size());
  if (!std::isnan(setup_[6])) sensor->setDetectionType(double_to_enum<prescan::api::types::DetectionType>(setup_[6]));
  if (!std::isnan(setup_[7])) sensor->setFov(setup_[7]);
  if (!std::isnan(setup_[8])) sensor->setMaxDetectableObjects(static_cast<std::int32_t>(setup_[8]));
  if (!std::isnan(setup_[9])) sensor->setRange(setup_[9]);
}
template <>
inline void Sensor::applySetup(prescan::api::brs::BrsSensor* const sensor) {
  if (setup_.size() != 12)
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: 12 != {}", sensor_type_, setup_.size());
  if (!std::isnan(setup_[6])) sensor->setFovHorizontal(setup_[6]);
  if (!std::isnan(setup_[7])) sensor->setFovVertical(setup_[7]);
  if (!std::isnan(setup_[8])) sensor->setFrequency(static_cast<std::int32_t>(setup_[8]));
  if (!std::isnan(setup_[9])) sensor->setMaxDetectableObjects(static_cast<std::int32_t>(setup_[9]));
  if (!std::isnan(setup_[10])) sensor->setResolutionX(static_cast<std::int32_t>(setup_[10]));
  if (!std::isnan(setup_[11])) sensor->setResolutionY(static_cast<std::int32_t>(setup_[11]));
}
template <>
inline void Sensor::applySetup(prescan::api::camera::CameraSensor* const sensor) {
  if (setup_.size() != 12)
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: 12 != {}", sensor_type_, setup_.size());
  if (!std::isnan(setup_[6])) sensor->imager().setWidth(setup_[6]);
  if (!std::isnan(setup_[7])) sensor->imager().setHeight(setup_[7]);
  if (!std::isnan(setup_[8])) sensor->imager().setResolutionX(static_cast<std::int32_t>(setup_[8]));
  if (!std::isnan(setup_[9])) sensor->imager().setResolutionY(static_cast<std::int32_t>(setup_[9]));
  if (!std::isnan(setup_[10])) sensor->setFocalLength(setup_[6]);
  if (!std::isnan(setup_[11])) sensor->setImageFormat(double_to_enum<prescan::api::camera::ImageFormat>(setup_[7]));
}
template <>
inline void Sensor::applySetup(prescan::api::lms::LmsSensor* const sensor) {
  if (setup_.size() != 11)
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: 11 != {}", sensor_type_, setup_.size());
  if (!std::isnan(setup_[6])) sensor->setFovHorizontal(setup_[6]);
  if (!std::isnan(setup_[7])) sensor->setMaxLines(static_cast<std::int32_t>(setup_[7]));
  if (!std::isnan(setup_[8])) sensor->setMaxPointsPerLine(static_cast<std::int32_t>(setup_[8]));
  if (!std::isnan(setup_[9])) sensor->setPointSpacing(setup_[9]);
  if (!std::isnan(setup_[10])) sensor->setRange(setup_[10]);
}
// template <>
// inline void Sensor::applySetupImpl<prescan::api::pcs::PcsSensor>() {
//   if (setup_.size() != 8)
//     SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: 8 != {}", sensor_type_, setup_.size());
//   prescan::api::pcs::PcsSensor& sensor = *static_cast<prescan::api::pcs::PcsSensor*>(sensor_.get());
//   if (!std::isnan(setup_[6])) sensor.setResolutionX(static_cast<std::int32_t>(setup_[6]));
//   if (!std::isnan(setup_[7])) sensor.setResolutionY(static_cast<std::int32_t>(setup_[7]));
// }

template <>
inline void Sensor::updateState<prescan::sim::AirSensorUnit>() {
  const prescan::sim::AirSensorUnit& sensor_unit = *static_cast<prescan::sim::AirSensorUnit*>(sensor_unit_.get());
  state_.clear();
  state_.reserve(sensor_unit.airSensorOutput().size() * 6);
  for (const auto& value : sensor_unit.airSensorOutput()) {
    state_.push_back(value->Range);
    state_.push_back(value->Azimuth);
    state_.push_back(value->Elevation);
    state_.push_back(static_cast<double>(value->ID));
    state_.push_back(value->Velocity);
    state_.push_back(value->Heading);
  }
}
template <>
inline void Sensor::updateState<prescan::sim::BrsSensorUnit>() {
  const prescan::sim::BrsSensorUnit& sensor_unit = *static_cast<prescan::sim::BrsSensorUnit*>(sensor_unit_.get());
  state_.clear();
  state_.reserve(sensor_unit.brsSensorOutput().size() * 5);
  for (const auto& value : sensor_unit.brsSensorOutput()) {
    state_.push_back(static_cast<double>(value->ObjectID));
    state_.push_back(value->Left);
    state_.push_back(value->Right);
    state_.push_back(value->Bottom);
    state_.push_back(value->Top);
  }
}
template <>
inline void Sensor::updateState<prescan::sim::CameraSensorUnit>() {
  const prescan::sim::CameraSensorUnit& sensor_unit = *static_cast<prescan::sim::CameraSensorUnit*>(sensor_unit_.get());
  state_.clear();
  image_ = sensor_unit.imageOutput();
}
// template <>
// inline void Sensor::updateStateImpl<prescan::sim::PcsSensorUnit>() {
//   const prescan::sim::PcsSensorUnit& sensor_unit = *static_cast<prescan::sim::PcsSensorUnit*>(sensor_unit_.get());
//   state_.clear();
//   sensor_unit.idOutput(0);
// }
template <>
inline void Sensor::updateState<prescan::sim::LmsSensorUnit>() {
  const prescan::sim::LmsSensorUnit& sensor_unit = *static_cast<prescan::sim::LmsSensorUnit*>(sensor_unit_.get());
  state_.clear();
  std::size_t total_size = 0;
  for (const auto& lines : sensor_unit.linesOutput()) total_size += lines.size() * 4;
  state_.reserve(total_size);
  for (const auto& lines : sensor_unit.linesOutput()) {
    for (const auto& value : lines) {
      state_.push_back(value.X);
      state_.push_back(value.Y);
      state_.push_back(value.Z);
      state_.push_back(value.Curvature);
    }
  }
}

template <>
void Sensor::updateState<prescan::sim::Unit>() {
  switch (sensor_type_) {
    case SensorType::AIR:
      updateState<prescan::sim::AirSensorUnit>();
      break;
    case SensorType::BRS:
      updateState<prescan::sim::BrsSensorUnit>();
      break;
    case SensorType::CAMERA:
      updateState<prescan::sim::CameraSensorUnit>();
      break;
    case SensorType::LMS:
      updateState<prescan::sim::LmsSensorUnit>();
      break;
    default:
      SYMAWARE_UNREACHABLE();
  }
}
template <>
inline void Sensor::applySetup(prescan::api::types::SensorBase* const sensor) {
  if (setup_.size() < 6)
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: {} < 6", sensor_type_, setup_.size());
  if (!std::isnan(setup_[0])) sensor->pose().position().setX(setup_[0]);
  if (!std::isnan(setup_[1])) sensor->pose().position().setY(setup_[1]);
  if (!std::isnan(setup_[2])) sensor->pose().position().setZ(setup_[2]);
  if (!std::isnan(setup_[3])) sensor->pose().orientation().setRoll(setup_[3]);
  if (!std::isnan(setup_[4])) sensor->pose().orientation().setPitch(setup_[4]);
  if (!std::isnan(setup_[5])) sensor->pose().orientation().setYaw(setup_[5]);
  switch (sensor_type_) {
    case SensorType::AIR:
      applySetup<prescan::api::air::AirSensor>(static_cast<prescan::api::air::AirSensor*>(sensor));
      break;
    case SensorType::BRS:
      applySetup<prescan::api::brs::BrsSensor>(static_cast<prescan::api::brs::BrsSensor*>(sensor));
      break;
    case SensorType::CAMERA:
      applySetup<prescan::api::camera::CameraSensor>(static_cast<prescan::api::camera::CameraSensor*>(sensor));
      break;
    case SensorType::LMS:
      applySetup<prescan::api::lms::LmsSensor>(static_cast<prescan::api::lms::LmsSensor*>(sensor));
      break;
    default:
      SYMAWARE_RUNTIME_ERROR_FMT("Sensor {} not yet implemented", sensor_type_);
  }
}

void Sensor::initialiseSensor(const prescan::api::types::WorldObject& object, const int id) {
  if (id_ != -1) SYMAWARE_RUNTIME_ERROR("Sensor already initialised");
  id_ = id;
  std::unique_ptr<prescan::api::types::SensorBase> sensor;
  switch (sensor_type_) {
    case SensorType::AIR:
      sensor = INITIALISE_SENSOR(existing_, air, Air, object, id);
      break;
    case SensorType::BRS:
      sensor = INITIALISE_SENSOR(existing_, brs, Brs, object, id);
      break;
    case SensorType::CAMERA:
      sensor = INITIALISE_SENSOR(existing_, camera, Camera, object, id);
      break;
    case SensorType::LMS:
      sensor = INITIALISE_SENSOR(existing_, lms, Lms, object, id);
      break;
    default:
      SYMAWARE_RUNTIME_ERROR_FMT("Sensor {} not yet implemented", sensor_type_);
  }
  applySetup(sensor.get());
}

void Sensor::registerUnit(const prescan::api::types::WorldObject& object,
                          const prescan::api::experiment::Experiment& experiment,
                          prescan::sim::ISimulation* simulation) {
  switch (sensor_type_) {
    case SensorType::AIR:
      REGISTER_SENSOR_UNIT(air, Air, object, id_);
      break;
    case SensorType::BRS:
      REGISTER_SENSOR_UNIT(brs, Brs, object, id_);
      break;
    case SensorType::CAMERA:
      REGISTER_SENSOR_UNIT(camera, Camera, object, id_);
      break;
    case SensorType::LMS:
      REGISTER_SENSOR_UNIT_ARGS(lms, Lms, object, id_, simulation->getSimulationPath());
      break;
    default:
      break;
  }
}
void Sensor::initialise(prescan::sim::ISimulation* simulation) {}
void Sensor::step(prescan::sim::ISimulation* simulation) { updateState<prescan::sim::Unit>(); }
void Sensor::terminate(prescan::sim::ISimulation* simulation) {}

}  // namespace symaware
