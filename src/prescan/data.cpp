#include "symaware/prescan/data.h"

#include <iomanip>
#include <iostream>

namespace symaware {

std::string to_string(const Gear gear) {
  switch (gear) {
    case Gear::Forward:
      return "Forward";
    case Gear::Neutral:
      return "Neutral";
    case Gear::Reverse:
      return "Reverse";
    case Gear::Undefined:
      return "Undefined";
    default:
      return "Unknown";
  }
}

std::ostream& operator<<(std::ostream& os, const Position& position) {
  return os << "Position: (x: " << position.x << ", y: " << position.y << ", z: " << position.z << ")";
}
std::ostream& operator<<(std::ostream& os, const Orientation& orientation) {
  return os << "Orientation: (roll: " << orientation.roll << ", pitch: " << orientation.pitch
            << ", yaw: " << orientation.yaw << ")";
}
std::ostream& operator<<(std::ostream& os, const Velocity& velocity) {
  return os << "Velocity: (x: " << velocity.x << ", y: " << velocity.y << ", z: " << velocity.z << ")";
}
std::ostream& operator<<(std::ostream& os, const Acceleration& acceleration) {
  return os << "Acceleration: (x: " << acceleration.x << ", y: " << acceleration.y << ", z: " << acceleration.z << ")";
}
std::ostream& operator<<(std::ostream& os, const AngularVelocity& angular_velocity) {
  return os << "AngularVelocity: (roll: " << angular_velocity.roll << ", pitch: " << angular_velocity.pitch
            << ", yaw: " << angular_velocity.yaw << ")";
}
std::ostream& operator<<(std::ostream& os, const CenterOfGravityOffset& cog_offset) {
  return os << "CenterOfGravityOffset: (x: " << cog_offset.x << ", y: " << cog_offset.y << ", z: " << cog_offset.z
            << ")";
}
std::ostream& operator<<(std::ostream& os, const DynamicalModelInput& dynamical_model_input) {
  return os << "DynamicalModelInput: (throttle: " << dynamical_model_input.throttle
            << ", brake: " << dynamical_model_input.brake
            << ", steering_wheel_angle(rad): " << dynamical_model_input.steering_wheel_angle
            << ", gear: " << to_string(dynamical_model_input.gear) << ")";
}
std::ostream& operator<<(std::ostream& os, const EntityState& entity_state) {
  return os << "EntittyState: (" << entity_state.position << ", " << entity_state.orientation
            << ", velocity: " << entity_state.velocity << ", yaw_rate: " << entity_state.yaw_rate << ")";
}
std::ostream& operator<<(std::ostream& os, const EntitySetup& entity_setup) {
  return os << std::boolalpha  // Enable the boolalpha
            << "EntitySetup: (" << entity_setup.position << ", " << entity_setup.orientation << ", "
            << entity_setup.cog_offset << ", collision_detectable: " << entity_setup.is_collision_detectable
            << ", movable: " << entity_setup.is_movable
            << ", sensor_detecatbility: " << entity_setup.sensor_detectability << ")"
            << std::noboolalpha;  // Remove the boolalpha
}

}  // namespace symaware
