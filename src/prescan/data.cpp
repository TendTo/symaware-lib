#include "symaware/prescan/data.h"

#include <iomanip>
#include <iostream>

namespace symaware {

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
std::ostream& operator<<(std::ostream& os, const ModelState& model_state) {
  return os << "ModelState: (" << model_state.position << ", " << model_state.orientation << ", "
            << model_state.acceleration << ", " << model_state.velocity << ", " << model_state.angular_velocity << ")";
}
std::ostream& operator<<(std::ostream& os, const EntityState& entity_state) {
  return os << std::boolalpha  // Enable the boolalpha
            << "EntityState: (" << entity_state.position << ", " << entity_state.orientation << ", "
            << entity_state.cog_offset << ", collision_detectable: " << entity_state.is_collision_detectable << ", movable: "
            << entity_state.is_movable << ", sensor_detecatbility: " << entity_state.sensor_detectability << ")"
            << std::noboolalpha;  // Remove the boolalpha
}

}  // namespace symaware
