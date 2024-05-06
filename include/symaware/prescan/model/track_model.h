/**
 * @file track_model.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief TrackModel class
 */
#pragma once

#include <fmt/ostream.h>

#include <iosfwd>
#include <limits>
#include <prescan/api/Trajectory.hpp>
#include <prescan/api/experiment/Experiment.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/PathUnit.hpp>
#include <prescan/sim/Simulation.hpp>
#include <prescan/sim/SpeedProfileUnit.hpp>
#include <prescan/sim/StateActuatorUnit.hpp>

#include "symaware/prescan/data.h"
#include "symaware/prescan/model/entity_model.h"

namespace symaware {

class TrackModel : public EntityModel {
 public:
  /**
   * @brief Construct a new TrackModel object with a default trajectory.
   * @param trajectory trajectory of the entity in the simulation
   */
  explicit TrackModel();
  /**
   * @brief Construct a new TrackModel object with the given @p path, @p speed and @p tolerance.
   *
   * These values will be used to create a trajectory.
   * @param path sequence of positions in the trajectory
   * @param speed speed the entity will move at to follow the path
   * @param tolerance tolerance of the path
   */
  explicit TrackModel(std::vector<Position> path, double speed, double tolerance);

  void initialiseObject(prescan::api::experiment::Experiment& experiment,
                        prescan::api::types::WorldObject object) override;

  void setInput(const std::vector<double>& input) override;
  void updateInput(const std::vector<double>& input) override;

  void registerUnit(const prescan::api::experiment::Experiment& experiment,
                    prescan::sim::ISimulation* simulation) override;

  const std::vector<Position>& trajectoryPath() const { return trajectory_path_; }
  double trajectorySpeed() const { return trajectory_speed_; }
  double trajectoryTolerance() const { return trajectory_tolerance_; }

 private:
  void updateState() override;
  std::vector<Position> trajectory_path_;  ///< The sequence of positions in the trajectory
  double trajectory_speed_;                ///< The speed used to determine the trajectory
  double trajectory_tolerance_;            ///< The tolerance of the trajectory

  prescan::sim::SpeedProfileUnit* speed_profile_;  ///< The speed profile of the entity in the simulation
  prescan::sim::PathUnit* path_;                   ///< The path of the trajectory of the entity in the simulation
};

std::ostream& operator<<(std::ostream& os, const TrackModel& track_model);

}  // namespace symaware
