#include "symaware/prescan/model/dynamical_model.h"

#include <fmt/core.h>

#include <cmath>
#include <prescan/api/Vehicledynamics.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/api/vehicledynamics/AmesimPreconfiguredDynamics.hpp>

#include "symaware/util/exception.h"

namespace symaware {

DynamicalModel::DynamicalModel(DynamicalModelInput initial_input) : EntityModel{}, input_{std::move(initial_input)} {}

void DynamicalModel::initialiseObject(prescan::api::experiment::Experiment& experiment,
                                      prescan::api::types::WorldObject object) {
  EntityModel::initialiseObject(experiment, object);
  prescan::api::vehicledynamics::createAmesimPreconfiguredDynamics(object_).setFlatGround(true);
}

void DynamicalModel::setInput(const DynamicalModelInput input) { input_ = std::move(input); }

void DynamicalModel::updateInput(const DynamicalModelInput& input) {
  if (!std::isnan(input.throttle)) input_.throttle = input.throttle;
  if (!std::isnan(input.brake)) input_.brake = input.brake;
  if (!std::isnan(input.steering_wheel_angle)) input_.steering_wheel_angle = input.steering_wheel_angle;
  if (input.gear != Gear::Undefined) input_.gear = input.gear;
}

void DynamicalModel::registerUnit(const prescan::api::experiment::Experiment& experiment,
                                  prescan::sim::ISimulation* simulation) {
  EntityModel::registerUnit(experiment, simulation);
  prescan::api::vehicledynamics::AmesimPreconfiguredDynamics dynamics =
      prescan::api::vehicledynamics::getAttachedAmesimPreconfiguredDynamics(object_);
  dynamics_ = prescan::sim::registerUnit<prescan::sim::AmesimVehicleDynamicsUnit>(simulation, dynamics);
}

void DynamicalModel::updateState() {
  SYMAWARE_ASSERT(state_ != nullptr, "DynamicalModel has not been registered to a state");
  fmt::println("Updating state with input: {}", input_);

  if (!std::isnan(input_.throttle)) dynamics_->vehicleControlInput().Throttle = input_.throttle;
  if (!std::isnan(input_.brake)) dynamics_->vehicleControlInput().Brake = input_.brake;
  if (!std::isnan(input_.steering_wheel_angle))
    dynamics_->vehicleControlInput().SteeringWheelAngle = input_.steering_wheel_angle;
  if (input_.gear != Gear::Undefined) dynamics_->vehicleControlInput().Gear = input_.gear;

  state_->stateActuatorInput() = dynamics_->stateActuatorOutput();
}

}  // namespace symaware
