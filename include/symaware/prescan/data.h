/**
 * @file data.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Data structures
 */
#pragma once

#include <fmt/ostream.h>

#include <iosfwd>
#include <limits>
#include <prescan/api/types/WorldObject.hpp>

static_assert(std::numeric_limits<double>::has_quiet_NaN, "IEEE 754 required");

namespace symaware {

enum Gear {
  Forward = 1,
  Neutral = 0,
  Reverse = -1,
  Undefined = 2,
};

struct Position {
  Position() = default;
  Position(double x, double y, double z) : x{x}, y{y}, z{z} {}
  explicit Position(bool zero_init)
      : x{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        y{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        z{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double x;
  double y;
  double z;
};

struct Orientation {
  Orientation() = default;
  Orientation(double roll, double pitch, double yaw) : roll{roll}, pitch{pitch}, yaw{yaw} {}
  explicit Orientation(bool zero_init)
      : roll{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        pitch{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        yaw{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double roll;
  double pitch;
  double yaw;
};

struct Velocity {
  Velocity() = default;
  Velocity(double x, double y, double z) : x{x}, y{y}, z{z} {}
  explicit Velocity(bool zero_init)
      : x{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        y{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        z{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double x;
  double y;
  double z;
};

struct Acceleration {
  Acceleration() = default;
  Acceleration(double x, double y, double z) : x{x}, y{y}, z{z} {}
  explicit Acceleration(bool zero_init)
      : x{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        y{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        z{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double x;
  double y;
  double z;
};

struct AngularVelocity {
  AngularVelocity() = default;
  AngularVelocity(double roll, double pitch, double yaw) : roll{roll}, pitch{pitch}, yaw{yaw} {}
  explicit AngularVelocity(bool zero_init)
      : roll{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        pitch{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        yaw{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double roll;
  double pitch;
  double yaw;
};

std::string to_string(Gear gear);
std::ostream& operator<<(std::ostream& os, const Position& position);
std::ostream& operator<<(std::ostream& os, const Orientation& orientation);
std::ostream& operator<<(std::ostream& os, const Velocity& velocity);
std::ostream& operator<<(std::ostream& os, const Acceleration& acceleration);
std::ostream& operator<<(std::ostream& os, const AngularVelocity& angular_velocity);

}  // namespace symaware

template <>
struct fmt::formatter<symaware::Position> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::Orientation> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::Velocity> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::Acceleration> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::AngularVelocity> : fmt::ostream_formatter {};
