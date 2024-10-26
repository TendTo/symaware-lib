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
  /** @brief Setup of the model */
  struct Setup {
    Setup() : existing{false}, active{false}, path{}, speed{0}, tolerance{0} {}
    Setup(bool existing, bool active, std::vector<Position> path, double speed, double tolerance)
        : existing{existing}, active{active}, path{std::move(path)}, speed{speed}, tolerance{tolerance} {}
    bool existing;
    bool active;
    std::vector<Position> path;
    double speed;
    double tolerance;
  };
  /** @brief The input of the model */
  struct Input {
    Input();
    explicit Input(bool zero_init);
    Input(double velocity_multiplier, double velocity_offset, double acceleration_multiplier,
          double acceleration_offset, double distance_multiplier, double distance_offset);
    double velocity_multiplier;      ///< Speed multiplier value. Default is 1
    double velocity_offset;          ///< Speed multiplier value. Default is 0
    double acceleration_multiplier;  ///< Acceleration multiplier value. Default is 1
    double acceleration_offset;      ///< Acceleration offset value. Default is 0
    double distance_multiplier;      ///< Distance multiplier value. Default is 1
    double distance_offset;          ///< Distance offset value. Default is 0
  };
  /**
   * @brief Construct a new TrackModel object with a default trajectory.
   * @param trajectory trajectory of the entity in the simulation
   */
  explicit TrackModel(const Setup& setup = {}, const Input& initial_input = Input{false});
  explicit TrackModel(const Input& initial_input);

  void createIfNotExists(prescan::api::experiment::Experiment& experiment) override;

  void setInput(const std::vector<double>& input) override;
  void updateInput(const std::vector<double>& input) override;

  /**
   * @brief Set the new control input of the model.
   * @param input model input to set
   */
  void setInput(Input input);
  /**
   * @brief Use the provided @p input to update the @ref input_ .
   *
   * Only the non-NaN values in the @p input will overwrite the corresponding values in the @ref input_ .
   * @param input model input used to update the current one
   */
  void updateInput(const Input& input);

  void registerUnit(const prescan::api::experiment::Experiment& experiment,
                    prescan::sim::ISimulation* simulation) override;

  const std::vector<Position>& trajectoryPositions() const { return trajectory_positions_; }
  std::vector<Pose> trajectoryPoses(std::size_t num_segments) const;
  double trajectorySpeed() const { return trajectory_speed_; }
  double trajectoryTolerance() const { return trajectory_tolerance_; }

 private:
  void updateState() override;
  std::vector<Position>
      trajectory_positions_;     ///< The sequence of positions in the trajectory. Used only for trajectory creation
  double trajectory_speed_;      ///< The speed used to determine the trajectory
  double trajectory_tolerance_;  ///< The tolerance of the trajectory
  prescan::api::trajectory::Trajectory trajectory_;  ///< The trajectory of the entity in the simulation

  prescan::sim::SpeedProfileUnit* speed_profile_;  ///< The speed profile of the entity in the simulation
  prescan::sim::PathUnit* path_;                   ///< The path of the trajectory of the entity in the simulation
  Input input_;                                    ///< The model state of the entity that will be applied each step
};

std::ostream& operator<<(std::ostream& os, const TrackModel::Input& input);
std::ostream& operator<<(std::ostream& os, const TrackModel& track_model);

}  // namespace symaware
