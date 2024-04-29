#include "symaware/prescan/model/track_model.h"

#include <fmt/core.h>

#include "symaware/util/exception.h"

namespace symaware {

TrackModel::TrackModel()
    : EntityModel{},
      trajectory_path_{},
      trajectory_speed_{0},
      trajectory_tolerance_{0},
      speed_profile_{nullptr},
      path_{nullptr} {}

TrackModel::TrackModel(std::vector<Position> path, const double speed, const double tolerance)
    : EntityModel{},
      trajectory_path_{std::move(path)},
      trajectory_speed_{speed},
      trajectory_tolerance_{tolerance},
      speed_profile_{nullptr},
      path_{nullptr} {}

void TrackModel::initialiseObject(prescan::api::experiment::Experiment& experiment,
                                  prescan::api::types::WorldObject object) {
  EntityModel::initialiseObject(experiment, object);
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
  prescan::api::trajectory::createTrajectory(object_, path, speed_profile);
}

void TrackModel::setInput(const std::vector<double>& input) {}

void TrackModel::updateInput(const std::vector<double>& input) {}

void TrackModel::registerUnit(const prescan::api::experiment::Experiment& experiment,
                              prescan::sim::ISimulation* simulation) {
  EntityModel::registerUnit(experiment, simulation);

  const prescan::api::trajectory::Trajectory trajectory = prescan::api::trajectory::getActiveTrajectory(object_);
  speed_profile_ = prescan::sim::registerUnit<prescan::sim::SpeedProfileUnit>(simulation, trajectory.speedProfile());
  path_ = prescan::sim::registerUnit<prescan::sim::PathUnit>(simulation, trajectory.path(), object_);
}

void TrackModel::updateState() {
  SYMAWARE_ASSERT(state_ != nullptr, "TrackModel has not been registered to a state");
  path_->motionInput() = speed_profile_->motionOutput();
  state_->stateActuatorInput() = path_->stateActuatorOutput();
}

}  // namespace symaware
