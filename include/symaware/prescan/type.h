/**
 * @file type.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Type enums
 */
#pragma once

#include <fmt/ostream.h>

#include <iosfwd>
#include <string>

namespace symaware {

enum class SensorType {
  AIR,
  ALMS,
  BRS,
  CAMERA,
  IR_BEACON,
  IR_OBU,
  RF_BEACON,
  RF_OBU,
  DEPTH_CAMERA,
  ISS,
  LIDA,
  LMS,
  OCS,
  PCS,
  PHYSICS_BASED_CAMERA_UNREAL,
  RADAR,
  TIS,
  TRAFFIC_SIGNAL,
  ULTRASONIC,
  WORLD_VIEWER,
};

enum Gear {
  Forward = 1,
  Neutral = 0,
  Reverse = -1,
  Undefined = 2,
};

std::string to_string(Gear gear);
std::string to_string(SensorType sensor_type);
std::ostream& operator<<(std::ostream& os, Gear gear);
std::ostream& operator<<(std::ostream& os, SensorType sensor_type);

}  // namespace symaware

template <>
struct fmt::formatter<symaware::Gear> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::SensorType> : fmt::ostream_formatter {};
