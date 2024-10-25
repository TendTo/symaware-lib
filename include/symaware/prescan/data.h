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

static_assert(std::numeric_limits<double>::has_quiet_NaN, "IEEE 754 required");

namespace symaware {

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

struct Pose {
  Pose() = default;
  Pose(double x, double y, double z, double roll, double pitch, double yaw)
      : position{x, y, z}, orientation{roll, pitch, yaw} {}
  explicit Pose(bool zero_init) : position{zero_init}, orientation{zero_init} {}
  Position position;
  Orientation orientation;
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

std::ostream& operator<<(std::ostream& os, const Position& position);
std::ostream& operator<<(std::ostream& os, const Orientation& orientation);
std::ostream& operator<<(std::ostream& os, const Pose& pose);
std::ostream& operator<<(std::ostream& os, const Velocity& velocity);
std::ostream& operator<<(std::ostream& os, const Acceleration& acceleration);
std::ostream& operator<<(std::ostream& os, const AngularVelocity& angular_velocity);

}  // namespace symaware

template <>
struct fmt::formatter<symaware::Position> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::Orientation> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::Pose> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::Velocity> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::Acceleration> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::AngularVelocity> : fmt::ostream_formatter {};
