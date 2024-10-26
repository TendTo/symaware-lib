#include "symaware/prescan/model/track_model.h"

#include <fmt/core.h>

#include "symaware/util/exception.h"

namespace symaware {

TrackModel::Input::Input()
    : velocity_multiplier{1},
      velocity_offset{0},
      acceleration_multiplier{1},
      acceleration_offset{0},
      distance_multiplier{1},
      distance_offset{0} {}

TrackModel::Input::Input(bool zero_init)
    : velocity_multiplier{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
      velocity_offset{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
      acceleration_multiplier{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
      acceleration_offset{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
      distance_multiplier{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
      distance_offset{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}

TrackModel::Input::Input(double velocity_multiplier, double velocity_offset, double acceleration_multiplier,
                         double acceleration_offset, double distance_multiplier, double distance_offset)
    : velocity_multiplier{velocity_multiplier},
      velocity_offset{velocity_offset},
      acceleration_multiplier{acceleration_multiplier},
      acceleration_offset{acceleration_offset},
      distance_multiplier{distance_multiplier},
      distance_offset{distance_offset} {}

TrackModel::TrackModel(const Setup& setup, const Input& initial_input)
    : EntityModel{setup.existing, setup.active},
      trajectory_positions_{setup.path},
      trajectory_speed_{setup.speed},
      trajectory_tolerance_{setup.tolerance},
      speed_profile_{nullptr},
      path_{nullptr},
      input_{initial_input} {}
TrackModel::TrackModel(const Input& initial_input) : TrackModel{{}, initial_input} {}

void TrackModel::createModel(const prescan::api::types::WorldObject& object,
                             prescan::api::experiment::Experiment& experiment) {
  if (existing_) return;
  EntityModel::createModel(object, experiment);
  std::vector<double> x, y, z;
  x.reserve(trajectory_positions_.size());
  y.reserve(trajectory_positions_.size());
  z.reserve(trajectory_positions_.size());
  for (const Position& position : trajectory_positions_) {
    x.push_back(position.x);
    y.push_back(position.y);
    z.push_back(position.z);
  }

  const prescan::api::trajectory::Path path{
      prescan::api::trajectory::createFittedPath(experiment, x, y, z, trajectory_tolerance_)};
  const prescan::api::trajectory::SpeedProfile speed_profile{
      prescan::api::trajectory::createSpeedProfileOfConstantSpeed(experiment, trajectory_speed_)};
  prescan::api::trajectory::createTrajectory(object, path, speed_profile);
}

void TrackModel::setInput(const std::vector<double>& input) {
  if (input.size() != 6)
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid input size for TrackModel: expected 6, got {}", input.size());
  input_ = Input{input[0], input[1], input[2], input[3], input[4], input[5]};
}

void TrackModel::updateInput(const std::vector<double>& input) {
  if (input.size() != 6)
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid input size for TrackModel: expected 6, got {}", input.size());
  if (!std::isnan(input[0])) input_.velocity_multiplier = input[0];
  if (!std::isnan(input[1])) input_.velocity_offset = input[1];
  if (!std::isnan(input[2])) input_.acceleration_multiplier = input[2];
  if (!std::isnan(input[3])) input_.acceleration_offset = input[3];
  if (!std::isnan(input[4])) input_.distance_multiplier = input[4];
  if (!std::isnan(input[5])) input_.distance_offset = input[5];
}

void TrackModel::setInput(Input input) { input_ = std::move(input); }
void TrackModel::updateInput(const Input& input) {
  if (!std::isnan(input.velocity_multiplier)) input_.velocity_multiplier = input.velocity_multiplier;
  if (!std::isnan(input.velocity_offset)) input_.velocity_offset = input.velocity_offset;
  if (!std::isnan(input.acceleration_multiplier)) input_.acceleration_multiplier = input.acceleration_multiplier;
  if (!std::isnan(input.acceleration_offset)) input_.acceleration_offset = input.acceleration_offset;
  if (!std::isnan(input.distance_multiplier)) input_.distance_multiplier = input.distance_multiplier;
  if (!std::isnan(input.distance_offset)) input_.distance_offset = input.distance_offset;
}

void TrackModel::registerUnit(const prescan::api::types::WorldObject& object,
                              const prescan::api::experiment::Experiment& experiment,
                              prescan::sim::ISimulation* simulation) {
  EntityModel::registerUnit(object, experiment, simulation);

  trajectory_ = prescan::api::trajectory::getActiveTrajectory(object);
  speed_profile_ = prescan::sim::registerUnit<prescan::sim::SpeedProfileUnit>(simulation, trajectory_.speedProfile());
  path_ = prescan::sim::registerUnit<prescan::sim::PathUnit>(simulation, trajectory_.path(), object);
}

std::vector<Pose> TrackModel::trajectoryPoses(const std::size_t num_segments) const {
  if (num_segments == 0) SYMAWARE_RUNTIME_ERROR("Divisions must be greater than 0");
  std::vector<Pose> poses;
  poses.reserve(num_segments);
  const double cons_distance = trajectory_.path().length() / num_segments;
  for (std::size_t i = 0; i < num_segments; ++i) {
    const double distance = i * cons_distance;
    const prescan::api::types::Pose& pose = trajectory_.path().poseAtDistance(distance);
    poses.emplace_back(pose.position().x(), pose.position().y(), pose.position().z(), pose.orientation().roll(),
                       pose.orientation().pitch(), pose.orientation().yaw());
  }
  return poses;
}

void TrackModel::updateState() {
  SYMAWARE_ASSERT(state_ != nullptr, "TrackModel has not been registered to a state");
  auto motion_output{speed_profile_->motionOutput()};
  if (!std::isnan(input_.velocity_multiplier)) motion_output.Velocity *= input_.velocity_multiplier;
  if (!std::isnan(input_.velocity_offset)) motion_output.Velocity += input_.velocity_offset;
  if (!std::isnan(input_.acceleration_multiplier)) motion_output.Acceleration *= input_.acceleration_multiplier;
  if (!std::isnan(input_.acceleration_offset)) motion_output.Acceleration += input_.acceleration_offset;
  if (!std::isnan(input_.distance_multiplier)) motion_output.Distance *= input_.distance_multiplier;
  if (!std::isnan(input_.distance_offset)) motion_output.Distance += input_.distance_offset;
  path_->motionInput() = motion_output;
  state_->stateActuatorInput() = path_->stateActuatorOutput();
}

std::ostream& operator<<(std::ostream& os, const TrackModel::Input& input) {
  return os << "TrackModel::Input: (velocity_multiplier: " << input.velocity_multiplier
            << ", velocity_offset: " << input.velocity_offset
            << ", acceleration_multiplier: " << input.acceleration_multiplier
            << ", acceleration_offset: " << input.acceleration_offset
            << ", distance_multiplier: " << input.distance_multiplier << ", distance_offset: " << input.distance_offset
            << ")";
}

std::ostream& operator<<(std::ostream& os, const TrackModel& track_model) {
  return os << "TrackModel(setup_trajectory_path: (";
  for (const Position& position : track_model.trajectoryPositions()) {
    os << position << ", ";
  }
  return os << "), trajectory_speed: " << track_model.trajectorySpeed()
            << ", trajectory_tolerance: " << track_model.trajectoryTolerance() << ")";
}

}  // namespace symaware
