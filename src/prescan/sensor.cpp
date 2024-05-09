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

#define CREATE_SENSOR(namespace, sensor_type)                                \
  sensor_ = std::make_unique<prescan::api::namespace ::sensor_type##Sensor>( \
      prescan::api::namespace ::create##sensor_type##Sensor(object));

#define REGISTER_SENSOR_UNIT(namespace, sensor_type)                                                          \
  sensor_unit_ =                                                                                              \
      std::make_unique<prescan::sim::Unit>(prescan::sim::registerUnit<prescan::sim::sensor_type##SensorUnit>( \
          simulation, *static_cast<prescan::api::namespace ::sensor_type##Sensor*>(sensor_.get())));

#define REGISTER_SENSOR_UNIT_ARGS(namespace, sensor_type, ...)                                                \
  sensor_unit_ =                                                                                              \
      std::make_unique<prescan::sim::Unit>(prescan::sim::registerUnit<prescan::sim::sensor_type##SensorUnit>( \
          simulation, *static_cast<prescan::api::namespace ::sensor_type##Sensor*>(sensor_.get()), __VA_ARGS__));

namespace symaware {

namespace {
template <class T>
inline T double_to_enum(const double value) {
  return static_cast<T>(static_cast<int>(value));
}

template <class T>
inline void to_state(const std::unique_ptr<T>& sensor_unit, std::vector<double>& state);

}  // namespace

Sensor::Sensor(const SensorType sensor_type, std::vector<double> setup = {})
    : sensor_type_{sensor_type}, setup_{std::move(setup)}, sensor_{nullptr} {
  switch (sensor_type_) {
    case SensorType::AIR:
    case SensorType::BRS:
    case SensorType::LMS:
      break;
    default:
      SYMAWARE_RUNTIME_ERROR_FMT("Sensor {} not yet implemented", sensor_type_);
  }
}

void Sensor::initialiseSensor(prescan::api::experiment::Experiment& experiment,
                              prescan::api::types::WorldObject object) {
  switch (sensor_type_) {
    case SensorType::AIR:
      CREATE_SENSOR(air, Air);
      break;
    case SensorType::BRS:
      CREATE_SENSOR(brs, Brs);
      break;
    case SensorType::LMS:
      CREATE_SENSOR(lms, Lms);
      break;
    default:
      SYMAWARE_RUNTIME_ERROR_FMT("Sensor {} not yet implemented", sensor_type_);
  }
  applySetup();
}

void Sensor::registerUnit(const prescan::api::experiment::Experiment& experiment,
                          prescan::sim::ISimulation* simulation) {
  switch (sensor_type_) {
    case SensorType::AIR:
      REGISTER_SENSOR_UNIT(air, Air);
      break;
    case SensorType::BRS:
      REGISTER_SENSOR_UNIT(brs, Brs);
    case SensorType::LMS:
      REGISTER_SENSOR_UNIT_ARGS(lms, Lms, simulation->getSimulationPath());
    default:
      break;
  }
}
void Sensor::initialise(prescan::sim::ISimulation* simulation) {}
void Sensor::step(prescan::sim::ISimulation* simulation) { updateState(); }
void Sensor::terminate(prescan::sim::ISimulation* simulation) {}

void Sensor::applySetup() {
  if (setup_.size() < 6)
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: {} < 6", sensor_type_, setup_.size());
  if (!std::isnan(setup_[0])) sensor_->pose().position().setX(setup_[0]);
  if (!std::isnan(setup_[1])) sensor_->pose().position().setY(setup_[1]);
  if (!std::isnan(setup_[2])) sensor_->pose().position().setZ(setup_[2]);
  if (!std::isnan(setup_[3])) sensor_->pose().orientation().setRoll(setup_[3]);
  if (!std::isnan(setup_[4])) sensor_->pose().orientation().setPitch(setup_[4]);
  if (!std::isnan(setup_[5])) sensor_->pose().orientation().setYaw(setup_[5]);
  switch (sensor_type_) {
    case SensorType::AIR:
      if (setup_.size() != 10)
        SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: 10 != {}", sensor_type_, setup_.size());
      if (!std::isnan(setup_[6]))
        static_cast<prescan::api::air::AirSensor*>(sensor_.get())
            ->setDetectionType(double_to_enum<prescan::api::types::DetectionType>(setup_[6]));
      if (!std::isnan(setup_[7])) static_cast<prescan::api::air::AirSensor*>(sensor_.get())->setFov(setup_[7]);
      if (!std::isnan(setup_[8]))
        static_cast<prescan::api::air::AirSensor*>(sensor_.get())
            ->setMaxDetectableObjects(static_cast<std::int32_t>(setup_[8]));
      if (!std::isnan(setup_[9])) static_cast<prescan::api::air::AirSensor*>(sensor_.get())->setRange(setup_[9]);
      break;
    case SensorType::BRS:
      if (setup_.size() != 12)
        SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: 12 != {}", sensor_type_, setup_.size());
      if (!std::isnan(setup_[6]))
        static_cast<prescan::api::brs::BrsSensor*>(sensor_.get())->setFovHorizontal(setup_[6]);
      if (!std::isnan(setup_[7])) static_cast<prescan::api::brs::BrsSensor*>(sensor_.get())->setFovVertical(setup_[7]);
      if (!std::isnan(setup_[8]))
        static_cast<prescan::api::brs::BrsSensor*>(sensor_.get())->setFrequency(static_cast<std::int32_t>(setup_[8]));
      if (!std::isnan(setup_[9]))
        static_cast<prescan::api::brs::BrsSensor*>(sensor_.get())
            ->setMaxDetectableObjects(static_cast<std::int32_t>(setup_[9]));
      if (!std::isnan(setup_[10]))
        static_cast<prescan::api::brs::BrsSensor*>(sensor_.get())
            ->setResolutionX(static_cast<std::int32_t>(setup_[10]));
      if (!std::isnan(setup_[11]))
        static_cast<prescan::api::brs::BrsSensor*>(sensor_.get())
            ->setResolutionY(static_cast<std::int32_t>(setup_[11]));
      break;
    case SensorType::LMS:
      if (setup_.size() != 11)
        SYMAWARE_RUNTIME_ERROR_FMT("Invalid setup size for sensor {}: 11 != {}", sensor_type_, setup_.size());
      if (!std::isnan(setup_[6]))
        static_cast<prescan::api::lms::LmsSensor*>(sensor_.get())->setFovHorizontal(setup_[6]);
      if (!std::isnan(setup_[7]))
        static_cast<prescan::api::lms::LmsSensor*>(sensor_.get())->setMaxLines(static_cast<std::int32_t>(setup_[7]));
      if (!std::isnan(setup_[8]))
        static_cast<prescan::api::lms::LmsSensor*>(sensor_.get())
            ->setMaxPointsPerLine(static_cast<std::int32_t>(setup_[8]));
      if (!std::isnan(setup_[9])) static_cast<prescan::api::lms::LmsSensor*>(sensor_.get())->setPointSpacing(setup_[9]);
      if (!std::isnan(setup_[10])) static_cast<prescan::api::lms::LmsSensor*>(sensor_.get())->setRange(setup_[10]);
    default:
      break;
  }
}

void Sensor::updateState() {
  switch (sensor_type_) {
    case SensorType::AIR:
      outputToState<prescan::sim::AirSensorUnit>();
      break;
    case SensorType::BRS:
      outputToState<prescan::sim::BrsSensorUnit>();
      break;
    case SensorType::LMS:
      outputToState<prescan::sim::LmsSensorUnit>();
    default:
      break;
  }
}

template <>
inline void Sensor::outputToState<prescan::sim::AirSensorUnit>() {
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
inline void Sensor::outputToState<prescan::sim::BrsSensorUnit>() {
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
inline void Sensor::outputToState<prescan::sim::LmsSensorUnit>() {
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

}  // namespace symaware
