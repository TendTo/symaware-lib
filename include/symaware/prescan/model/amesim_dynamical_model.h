/**
 * @file amesim_dynamical_model.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief AmesimDynamicalModel class
 */
#pragma once

#include <fmt/ostream.h>

#include <iosfwd>
#include <limits>
#include <prescan/api/experiment/Experiment.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/AmesimVehicleDynamicsUnit.hpp>
#include <prescan/sim/Simulation.hpp>
#include <prescan/sim/StateActuatorUnit.hpp>

#include "symaware/prescan/data.h"
#include "symaware/prescan/model/entity_model.h"

namespace symaware {

class AmesimDynamicalModel : public EntityModel {
 public:
  /** @brief The input of the model */
  struct Input {
    Input() = default;
    explicit Input(bool zero_init);
    Input(double throttle, double brake, double steering_wheel_angle, Gear gear);
    double throttle;              ///< Throttle value in the range [0, 1]
    double brake;                 ///< Brake value in the range [0, 1]
    double steering_wheel_angle;  ///< Steering wheel angle in radians
    Gear gear;                    ///< Gear of the vehicle. Neutral is 0, Forward is 1, Reverse is -1, Undefined is 2
  };

  /**
   * @brief Construct a new Dynamical Model object with an initial model state.
   * @param state initial model state
   */
  explicit AmesimDynamicalModel(Input initial_input = Input{false});

  void initialiseObject(prescan::api::experiment::Experiment& experiment,
                        prescan::api::types::WorldObject object) override;
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

  void setInput(const std::vector<double>& input) override;
  void updateInput(const std::vector<double>& input) override;

  void registerUnit(const prescan::api::experiment::Experiment& experiment,
                    prescan::sim::ISimulation* simulation) override;

  const Input& input() const { return input_; }

 private:
  void updateState() override;

  prescan::sim::AmesimVehicleDynamicsUnit* dynamics_;  ///< The dynamics of the entity in the simulation
  Input input_;                                        ///< The model state of the entity that will be applied each step
};

std::ostream& operator<<(std::ostream& os, const AmesimDynamicalModel::Input& input);
std::ostream& operator<<(std::ostream& os, const AmesimDynamicalModel& amesim_dynamical_model);

}  // namespace symaware

template <>
struct fmt::formatter<symaware::AmesimDynamicalModel::Input> : fmt::ostream_formatter {};
