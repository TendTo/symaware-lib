#include "symaware/prescan/dynamical_model.h"

#include <fmt/core.h>

#include <cmath>
#include <prescan/api/types/WorldObject.hpp>

#include "symaware/util/exception.h"

namespace symaware {

DynamicalModel::DynamicalModel(State state) : object_{}, state_{nullptr}, state_input_{std::move(state)} {}

void DynamicalModel::initialiseObject(prescan::api::types::WorldObject object) { object_ = object; }

void DynamicalModel::setState(State state) { state_input_ = std::move(state); }

void DynamicalModel::registerUnit(prescan::api::experiment::Experiment& experiment,
                                  prescan::sim::ISimulation* simulation) {
  if (state_ != nullptr) SYMAWARE_RUNTIME_ERROR("DynamicalModel has alreasy been registered to a state");
  state_ = prescan::sim::registerUnit<prescan::sim::StateActuatorUnit>(simulation, object_);
}

void DynamicalModel::initialise(prescan::sim::ISimulation* simulation) {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("DynamicalModel has not been registered to a state");
  fmt::println("DynamicalModel::step\nState: {}", state_input_);
  fmt::println("Current state: {}", state_->stateActuatorInput());
  updateState();
}

void DynamicalModel::step(prescan::sim::ISimulation* simulation) {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("DynamicalModel has not been registered to a state");
  updateState();
}

void DynamicalModel::terminate(prescan::sim::ISimulation* simulation) {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("DynamicalModel has not been registered to a state");
  state_ = nullptr;
}

void DynamicalModel::updateState() {
  if (!std::isnan(state_input_.acceleration.x))
    state_->stateActuatorInput().AccelerationX = state_input_.acceleration.x;
  if (!std::isnan(state_input_.acceleration.y))
    state_->stateActuatorInput().AccelerationY = state_input_.acceleration.y;
  if (!std::isnan(state_input_.acceleration.z))
    state_->stateActuatorInput().AccelerationZ = state_input_.acceleration.z;

  if (!std::isnan(state_input_.position.x)) state_->stateActuatorInput().PositionX = state_input_.position.x;
  if (!std::isnan(state_input_.position.y)) state_->stateActuatorInput().PositionY = state_input_.position.y;
  if (!std::isnan(state_input_.position.z)) state_->stateActuatorInput().PositionZ = state_input_.position.z;

  if (!std::isnan(state_input_.orientation.roll))
    state_->stateActuatorInput().OrientationPitch = state_input_.orientation.roll;
  if (!std::isnan(state_input_.orientation.pitch))
    state_->stateActuatorInput().OrientationRoll = state_input_.orientation.pitch;
  if (!std::isnan(state_input_.orientation.yaw))
    state_->stateActuatorInput().OrientationYaw = state_input_.orientation.yaw;
  if (!std::isnan(state_input_.angular_velocity.pitch))
    state_->stateActuatorInput().AngularVelocityPitch = state_input_.angular_velocity.pitch;
  if (!std::isnan(state_input_.angular_velocity.roll))
    state_->stateActuatorInput().AngularVelocityRoll = state_input_.angular_velocity.roll;
  if (!std::isnan(state_input_.angular_velocity.yaw))
    state_->stateActuatorInput().AngularVelocityYaw = state_input_.angular_velocity.yaw;

  if (!std::isnan(state_input_.velocity.x)) state_->stateActuatorInput().VelocityX = state_input_.velocity.x;
  if (!std::isnan(state_input_.velocity.y)) state_->stateActuatorInput().VelocityY = state_input_.velocity.y;
  if (!std::isnan(state_input_.velocity.z)) state_->stateActuatorInput().VelocityZ = state_input_.velocity.z;
}
}  // namespace symaware