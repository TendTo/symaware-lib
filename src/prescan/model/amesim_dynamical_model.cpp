#include "symaware/prescan/model/amesim_dynamical_model.h"

#include <fmt/core.h>

#include <cmath>
#include <prescan/api/Vehicledynamics.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/api/vehicledynamics/AmesimPreconfiguredDynamics.hpp>

#include "symaware/util/exception.h"

namespace symaware {

AmesimDynamicalModel::AmesimDynamicalModel(Input initial_input) : EntityModel{}, input_{std::move(initial_input)} {}

void AmesimDynamicalModel::initialiseObject(prescan::api::experiment::Experiment& experiment,
                                            prescan::api::types::WorldObject object) {
  EntityModel::initialiseObject(experiment, object);
  prescan::api::vehicledynamics::createAmesimPreconfiguredDynamics(object_).setFlatGround(true);
}

void AmesimDynamicalModel::setInput(const std::vector<double>& input) {
  if (input.size() != 4) {
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid input size for AmesimDynamicalModel: expected 4, got {}", input.size());
  }
  input_ = Input{input[0], input[1], input[2], static_cast<Gear>(static_cast<int>(input[3]))};
}

void AmesimDynamicalModel::updateInput(const std::vector<double>& input) {
  if (input.size() != 4) {
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid input size for AmesimDynamicalModel: expected 4, got {}", input.size());
  }
  if (!std::isnan(input[0])) input_.throttle = input[0];
  if (!std::isnan(input[1])) input_.brake = input[1];
  if (!std::isnan(input[2])) input_.steering_wheel_angle = input[2];
  if (!std::isnan(input[3]) && input[3] != static_cast<int>(Gear::Undefined))
    input_.gear = static_cast<Gear>(static_cast<int>(input[3]));
}

void AmesimDynamicalModel::setInput(const Input input) { input_ = std::move(input); }

void AmesimDynamicalModel::updateInput(const Input& input) {
  if (!std::isnan(input.throttle)) input_.throttle = input.throttle;
  if (!std::isnan(input.brake)) input_.brake = input.brake;
  if (!std::isnan(input.steering_wheel_angle)) input_.steering_wheel_angle = input.steering_wheel_angle;
  if (input.gear != Gear::Undefined) input_.gear = input.gear;
}

void AmesimDynamicalModel::registerUnit(const prescan::api::experiment::Experiment& experiment,
                                        prescan::sim::ISimulation* simulation) {
  EntityModel::registerUnit(experiment, simulation);
  prescan::api::vehicledynamics::AmesimPreconfiguredDynamics dynamics =
      prescan::api::vehicledynamics::getAttachedAmesimPreconfiguredDynamics(object_);
  dynamics_ = prescan::sim::registerUnit<prescan::sim::AmesimVehicleDynamicsUnit>(simulation, dynamics);
}

void AmesimDynamicalModel::updateState() {
  SYMAWARE_ASSERT(state_ != nullptr, "AmesimDynamicalModel has not been registered to a state");
  fmt::println("Updating state with input: {}", input_);

  if (!std::isnan(input_.throttle)) dynamics_->vehicleControlInput().Throttle = input_.throttle;
  if (!std::isnan(input_.brake)) dynamics_->vehicleControlInput().Brake = input_.brake;
  if (!std::isnan(input_.steering_wheel_angle))
    dynamics_->vehicleControlInput().SteeringWheelAngle = input_.steering_wheel_angle;
  if (input_.gear != Gear::Undefined) dynamics_->vehicleControlInput().Gear = input_.gear;

  state_->stateActuatorInput() = dynamics_->stateActuatorOutput();
}

std::ostream& operator<<(std::ostream& os, const AmesimDynamicalModel::Input& input) {
  return os << "AmesimDynamicalModel::Input: (throttle: " << input.throttle << ", brake: " << input.brake
            << ", steering_wheel_angle: " << input.steering_wheel_angle << ", gear: " << to_string(input.gear) << ")";
}

}  // namespace symaware
