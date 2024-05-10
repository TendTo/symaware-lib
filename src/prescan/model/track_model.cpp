#include "symaware/prescan/model/track_model.h"

#include <fmt/core.h>

#include "symaware/util/exception.h"

namespace symaware {

TrackModel::TrackModel(const Setup& setup)
    : EntityModel{setup.existing},
      trajectory_path_{setup.path},
      trajectory_speed_{setup.speed},
      trajectory_tolerance_{setup.tolerance},
      speed_profile_{nullptr},
      path_{nullptr} {}

void TrackModel::createModel(const prescan::api::types::WorldObject& object,
                             prescan::api::experiment::Experiment& experiment) {
  if (existing_) return;
  EntityModel::createModel(object, experiment);
  std::vector<double> x, y, z;
  x.reserve(trajectory_path_.size());
  y.reserve(trajectory_path_.size());
  z.reserve(trajectory_path_.size());
  for (const Position& position : trajectory_path_) {
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

void TrackModel::setInput(const std::vector<double>& input) {}

void TrackModel::updateInput(const std::vector<double>& input) {}

void TrackModel::registerUnit(const prescan::api::types::WorldObject& object,
                              const prescan::api::experiment::Experiment& experiment,
                              prescan::sim::ISimulation* simulation) {
  EntityModel::registerUnit(object, experiment, simulation);

  const prescan::api::trajectory::Trajectory trajectory = prescan::api::trajectory::getActiveTrajectory(object);
  speed_profile_ = prescan::sim::registerUnit<prescan::sim::SpeedProfileUnit>(simulation, trajectory.speedProfile());
  path_ = prescan::sim::registerUnit<prescan::sim::PathUnit>(simulation, trajectory.path(), object);
}

void TrackModel::updateState() {
  SYMAWARE_ASSERT(state_ != nullptr, "TrackModel has not been registered to a state");
  path_->motionInput() = speed_profile_->motionOutput();
  state_->stateActuatorInput() = path_->stateActuatorOutput();
}

std::ostream& operator<<(std::ostream& os, const TrackModel& track_model) {
  return os << "TrackModel(trajectory_path: (";
  for (const Position& position : track_model.trajectoryPath()) {
    os << position << ", ";
  }
  return os << "), trajectory_speed: " << track_model.trajectorySpeed()
            << ", trajectory_tolerance: " << track_model.trajectoryTolerance() << ")";
}

}  // namespace symaware
