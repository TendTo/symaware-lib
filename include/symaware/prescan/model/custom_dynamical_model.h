/**
 * @file custom_dynamical_model.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief CustomDynamicalModel class
 */
#pragma once

#include <fmt/ostream.h>

#include <iosfwd>
#include <limits>
#include <prescan/api/experiment/Experiment.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/Simulation.hpp>
#include <prescan/sim/StateActuatorUnit.hpp>

#include "symaware/prescan/data.h"
#include "symaware/prescan/model/entity_model.h"

namespace symaware {

class CustomDynamicalModel : public EntityModel {
 public:
  struct Setup {
    Setup() : existing{false}, active{true} {}
    Setup(bool existing, bool active) : existing{existing}, active{active} {}
    bool existing;
    bool active;
  };
  /** @brief The input of the model */
  struct Input {
    Input() = default;
    explicit Input(bool zero_init);
    Input(Position position, Orientation orientation, Acceleration acceleration, Velocity velocity,
          AngularVelocity angular_velocity);
    Position position;
    Orientation orientation;
    Acceleration acceleration;
    Velocity velocity;
    AngularVelocity angular_velocity;
  };

  /**
   * @brief Construct a new Dynamical Model object with an initial model state.
   * @param state initial model state
   */
  explicit CustomDynamicalModel(Input initial_input = Input{false});
  CustomDynamicalModel(const Setup& setup, Input initial_input = Input{false});

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

  const Input& input() const { return input_; }

 private:
  void updateState() override;

  Input input_;  ///< The model state of the entity that will be applied each step
};

std::ostream& operator<<(std::ostream& os, const CustomDynamicalModel::Input& input);
std::ostream& operator<<(std::ostream& os, const CustomDynamicalModel& custom_dynamical_model);

}  // namespace symaware

template <>
struct fmt::formatter<symaware::CustomDynamicalModel::Input> : fmt::ostream_formatter {};
