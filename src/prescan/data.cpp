#include "symaware/prescan/data.h"

#include <iomanip>
#include <iostream>

#include "symaware/util/exception.h"

namespace symaware {
std::ostream& operator<<(std::ostream& os, const Position& position) {
  return os << "Position: (x: " << position.x << ", y: " << position.y << ", z: " << position.z << ")";
}
std::ostream& operator<<(std::ostream& os, const Orientation& orientation) {
  return os << "Orientation: (roll: " << orientation.roll << ", pitch: " << orientation.pitch
            << ", yaw: " << orientation.yaw << ")";
}
std::ostream& operator<<(std::ostream& os, const Pose& pose) {
  return os << "Pose: (position: " << pose.position << ", orientation: " << pose.orientation << ")";
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

}  // namespace symaware
