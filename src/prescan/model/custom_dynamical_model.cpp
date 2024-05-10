#include "symaware/prescan/model/custom_dynamical_model.h"

#include <fmt/core.h>

#include <cmath>
#include <ostream>
#include <prescan/api/Vehicledynamics.hpp>
#include <prescan/api/types/WorldObject.hpp>

#include "symaware/util/exception.h"

namespace symaware {

CustomDynamicalModel::Input::Input(Position position, Orientation orientation, Acceleration acceleration,
                                   Velocity velocity, AngularVelocity angular_velocity)
    : position{position},
      orientation{orientation},
      acceleration{acceleration},
      velocity{velocity},
      angular_velocity{angular_velocity} {}
CustomDynamicalModel::Input::Input(bool zero_init)
    : position{zero_init},
      orientation{zero_init},
      acceleration{zero_init},
      velocity{zero_init},
      angular_velocity{zero_init} {}

CustomDynamicalModel::CustomDynamicalModel(Input initial_input) : CustomDynamicalModel{{}, initial_input} {}
CustomDynamicalModel::CustomDynamicalModel(const Setup& setup, Input initial_input)
    : EntityModel{setup.existing}, input_{std::move(initial_input)} {}

void CustomDynamicalModel::setInput(const std::vector<double>& input) {
  if (input.size() != 15) {
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid input size for CustomDynamicalModel: expected 4, got {}", input.size());
  }
  input_ = Input{{input[0], input[1], input[2]},
                 {input[3], input[4], input[5]},
                 {input[6], input[7], input[8]},
                 {input[9], input[10], input[11]},
                 {input[12], input[13], input[14]}};
}

void CustomDynamicalModel::updateInput(const std::vector<double>& input) {
  if (input.size() != 15) {
    SYMAWARE_RUNTIME_ERROR_FMT("Invalid input size for CustomDynamicalModel: expected 4, got {}", input.size());
  }
  if (!std::isnan(input[0])) input_.position.x = input[0];
  if (!std::isnan(input[1])) input_.position.y = input[1];
  if (!std::isnan(input[2])) input_.position.z = input[2];

  if (!std::isnan(input[3])) input_.orientation.roll = input[3];
  if (!std::isnan(input[4])) input_.orientation.pitch = input[4];
  if (!std::isnan(input[5])) input_.orientation.yaw = input[5];

  if (!std::isnan(input[6])) input_.acceleration.x = input[6];
  if (!std::isnan(input[7])) input_.acceleration.y = input[7];
  if (!std::isnan(input[8])) input_.acceleration.z = input[8];

  if (!std::isnan(input[9])) input_.velocity.x = input[9];
  if (!std::isnan(input[10])) input_.velocity.y = input[10];
  if (!std::isnan(input[11])) input_.velocity.z = input[11];

  if (!std::isnan(input[12])) input_.angular_velocity.roll = input[12];
  if (!std::isnan(input[13])) input_.angular_velocity.pitch = input[13];
  if (!std::isnan(input[14])) input_.angular_velocity.yaw = input[14];
}

void CustomDynamicalModel::setInput(const Input input) { input_ = std::move(input); }

void CustomDynamicalModel::updateInput(const Input& input) {
  if (!std::isnan(input.acceleration.x)) input_.acceleration.x = input.acceleration.x;
  if (!std::isnan(input.acceleration.y)) input_.acceleration.y = input.acceleration.y;
  if (!std::isnan(input.acceleration.z)) input_.acceleration.z = input.acceleration.z;

  if (!std::isnan(input.position.x)) input_.position.x = input.position.x;
  if (!std::isnan(input.position.y)) input_.position.y = input.position.y;
  if (!std::isnan(input.position.z)) input_.position.z = input.position.z;

  if (!std::isnan(input.orientation.roll)) input_.orientation.roll = input.orientation.roll;
  if (!std::isnan(input.orientation.pitch)) input_.orientation.pitch = input.orientation.pitch;
  if (!std::isnan(input.orientation.yaw)) input_.orientation.yaw = input.orientation.yaw;

  if (!std::isnan(input.angular_velocity.pitch)) input_.angular_velocity.pitch = input.angular_velocity.pitch;
  if (!std::isnan(input.angular_velocity.roll)) input_.angular_velocity.roll = input.angular_velocity.roll;
  if (!std::isnan(input.angular_velocity.yaw)) input_.angular_velocity.yaw = input.angular_velocity.yaw;

  if (!std::isnan(input.velocity.x)) input_.velocity.x = input.velocity.x;
  if (!std::isnan(input.velocity.y)) input_.velocity.y = input.velocity.y;
  if (!std::isnan(input.velocity.z)) input_.velocity.z = input.velocity.z;
}

void CustomDynamicalModel::updateState() {
  SYMAWARE_ASSERT(state_ != nullptr, "CustomDynamicalModel has not been registered to a state");
  if (!std::isnan(input_.acceleration.x)) state_->stateActuatorInput().AccelerationX = input_.acceleration.x;
  if (!std::isnan(input_.acceleration.y)) state_->stateActuatorInput().AccelerationY = input_.acceleration.y;
  if (!std::isnan(input_.acceleration.z)) state_->stateActuatorInput().AccelerationZ = input_.acceleration.z;

  if (!std::isnan(input_.position.x)) state_->stateActuatorInput().PositionX = input_.position.x;
  if (!std::isnan(input_.position.y)) state_->stateActuatorInput().PositionY = input_.position.y;
  if (!std::isnan(input_.position.z)) state_->stateActuatorInput().PositionZ = input_.position.z;

  if (!std::isnan(input_.orientation.roll)) state_->stateActuatorInput().OrientationPitch = input_.orientation.roll;
  if (!std::isnan(input_.orientation.pitch)) state_->stateActuatorInput().OrientationRoll = input_.orientation.pitch;
  if (!std::isnan(input_.orientation.yaw)) state_->stateActuatorInput().OrientationYaw = input_.orientation.yaw;
  if (!std::isnan(input_.angular_velocity.pitch))
    state_->stateActuatorInput().AngularVelocityPitch = input_.angular_velocity.pitch;
  if (!std::isnan(input_.angular_velocity.roll))
    state_->stateActuatorInput().AngularVelocityRoll = input_.angular_velocity.roll;
  if (!std::isnan(input_.angular_velocity.yaw))
    state_->stateActuatorInput().AngularVelocityYaw = input_.angular_velocity.yaw;

  if (!std::isnan(input_.velocity.x)) state_->stateActuatorInput().VelocityX = input_.velocity.x;
  if (!std::isnan(input_.velocity.y)) state_->stateActuatorInput().VelocityY = input_.velocity.y;
  if (!std::isnan(input_.velocity.z)) state_->stateActuatorInput().VelocityZ = input_.velocity.z;
}

std::ostream& operator<<(std::ostream& os, const CustomDynamicalModel::Input& input) {
  return os << "CustomDynamicalModel::Input: (" << input.position << ", " << input.orientation << ", "
            << input.acceleration << ", " << input.velocity << ", " << input.angular_velocity << ")";
}
std::ostream& operator<<(std::ostream& os, const CustomDynamicalModel& custom_dynamical_model) {
  return os << "CustomDynamicalModel(input: " << custom_dynamical_model.input() << ")";
}

}  // namespace symaware
