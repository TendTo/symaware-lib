#include "symaware/prescan/dynamical_model.h"

#include <fmt/core.h>

#include <cmath>
#include <prescan/api/types/WorldObject.hpp>

#include "symaware/util/exception.h"

namespace symaware {

DynamicalModel::DynamicalModel(ModelState state) : object_{}, state_{nullptr}, model_state_{std::move(state)} {}

void DynamicalModel::initialiseObject(prescan::api::types::WorldObject object) { object_ = object; }

void DynamicalModel::setState(ModelState state) { model_state_ = std::move(state); }

void DynamicalModel::registerUnit(const prescan::api::experiment::Experiment& experiment,
                                  prescan::sim::ISimulation* simulation) {
  if (state_ != nullptr) SYMAWARE_RUNTIME_ERROR("DynamicalModel has alreasy been registered to a state");
  state_ = prescan::sim::registerUnit<prescan::sim::StateActuatorUnit>(simulation, object_);
}

void DynamicalModel::initialise(prescan::sim::ISimulation* simulation) {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("DynamicalModel has not been registered to a state");
  fmt::println("DynamicalModel::step\nState: {}", model_state_);
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
  if (!std::isnan(model_state_.acceleration.x))
    state_->stateActuatorInput().AccelerationX = model_state_.acceleration.x;
  if (!std::isnan(model_state_.acceleration.y))
    state_->stateActuatorInput().AccelerationY = model_state_.acceleration.y;
  if (!std::isnan(model_state_.acceleration.z))
    state_->stateActuatorInput().AccelerationZ = model_state_.acceleration.z;

  if (!std::isnan(model_state_.position.x)) state_->stateActuatorInput().PositionX = model_state_.position.x;
  if (!std::isnan(model_state_.position.y)) state_->stateActuatorInput().PositionY = model_state_.position.y;
  if (!std::isnan(model_state_.position.z)) state_->stateActuatorInput().PositionZ = model_state_.position.z;

  if (!std::isnan(model_state_.orientation.roll))
    state_->stateActuatorInput().OrientationPitch = model_state_.orientation.roll;
  if (!std::isnan(model_state_.orientation.pitch))
    state_->stateActuatorInput().OrientationRoll = model_state_.orientation.pitch;
  if (!std::isnan(model_state_.orientation.yaw))
    state_->stateActuatorInput().OrientationYaw = model_state_.orientation.yaw;
  if (!std::isnan(model_state_.angular_velocity.pitch))
    state_->stateActuatorInput().AngularVelocityPitch = model_state_.angular_velocity.pitch;
  if (!std::isnan(model_state_.angular_velocity.roll))
    state_->stateActuatorInput().AngularVelocityRoll = model_state_.angular_velocity.roll;
  if (!std::isnan(model_state_.angular_velocity.yaw))
    state_->stateActuatorInput().AngularVelocityYaw = model_state_.angular_velocity.yaw;

  if (!std::isnan(model_state_.velocity.x)) state_->stateActuatorInput().VelocityX = model_state_.velocity.x;
  if (!std::isnan(model_state_.velocity.y)) state_->stateActuatorInput().VelocityY = model_state_.velocity.y;
  if (!std::isnan(model_state_.velocity.z)) state_->stateActuatorInput().VelocityZ = model_state_.velocity.z;
}
}  // namespace symaware