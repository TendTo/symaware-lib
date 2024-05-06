#include "symaware/prescan/model/amesim_dynamical_model.h"

#include <fmt/core.h>

#include <cmath>
#include <ostream>
#include <prescan/api/Vehicledynamics.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/api/vehicledynamics/AmesimPreconfiguredDynamics.hpp>

#include "symaware/util/exception.h"

namespace symaware {

AmesimDynamicalModel::Input::Input(bool zero_init)
    : throttle{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
      brake{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
      steering_wheel_angle{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
      gear{zero_init ? Gear::Neutral : Gear::Undefined} {}

AmesimDynamicalModel::Input::Input(double throttle, double brake, double steering_wheel_angle, Gear gear)
    : throttle{throttle}, brake{brake}, steering_wheel_angle{steering_wheel_angle}, gear{gear} {}

AmesimDynamicalModel::AmesimDynamicalModel(Input initial_input)
    : AmesimDynamicalModel{true, std::move(initial_input)} {}
AmesimDynamicalModel::AmesimDynamicalModel(const bool is_flat_ground, Input initial_input)
    : EntityModel{}, is_flat_ground_{is_flat_ground}, input_{std::move(initial_input)} {}

void AmesimDynamicalModel::initialiseObject(prescan::api::experiment::Experiment& experiment,
                                            prescan::api::types::WorldObject object) {
  EntityModel::initialiseObject(experiment, object);
  prescan::api::vehicledynamics::createAmesimPreconfiguredDynamics(object_).setFlatGround(is_flat_ground_);
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
  dynamics_ = prescan::sim::registerUnit<prescan::sim::AmesimVehicleDynamicsUnit>(
      simulation, dynamics, is_flat_ground_ ? std::string{} : simulation->getSimulationPath());
}

void AmesimDynamicalModel::updateState() {
  SYMAWARE_ASSERT(state_ != nullptr, "AmesimDynamicalModel has not been registered to a state");
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

std::ostream& operator<<(std::ostream& os, const AmesimDynamicalModel& amesim_dynamical_model) {
  return os << "AmesimDynamicalModel(input: " << amesim_dynamical_model.input() << ")";
}

}  // namespace symaware
