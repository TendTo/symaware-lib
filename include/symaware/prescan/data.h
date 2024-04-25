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

struct CenterOfGravityOffset {
  CenterOfGravityOffset() = default;
  CenterOfGravityOffset(double x, double y, double z) : x{x}, y{y}, z{z} {}
  explicit CenterOfGravityOffset(bool zero_init)
      : x{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        y{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        z{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double x;
  double y;
  double z;
};

struct ModelState {
  ModelState() = default;
  ModelState(Position position, Orientation orientation, Acceleration acceleration, Velocity velocity,
             AngularVelocity angular_velocity)
      : position{position},
        orientation{orientation},
        acceleration{acceleration},
        velocity{velocity},
        angular_velocity{angular_velocity} {}
  explicit ModelState(bool zero_init)
      : position{zero_init},
        orientation{zero_init},
        acceleration{zero_init},
        velocity{zero_init},
        angular_velocity{zero_init} {}
  Position position;
  Orientation orientation;
  Acceleration acceleration;
  Velocity velocity;
  AngularVelocity angular_velocity;
};

struct EntityState {
  EntityState() = default;
  EntityState(Position position, Orientation orientation, double velocity, double yaw_rate)
      : position{position}, orientation{orientation}, velocity{velocity}, yaw_rate{yaw_rate} {}
  explicit EntityState(bool zero_init)
      : position{zero_init},
        orientation{zero_init},
        velocity{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        yaw_rate{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  Position position;
  Orientation orientation;
  double velocity;
  double yaw_rate;
};

struct EntitySetup {
  EntitySetup() = default;
  EntitySetup(Position position, Orientation orientation, CenterOfGravityOffset cog_offset,
              bool is_collision_detectable, bool is_movable,
              prescan::api::types::SensorDetectability sensor_detectability)
      : position{position},
        orientation{orientation},
        cog_offset{cog_offset},
        is_collision_detectable{is_collision_detectable},
        is_movable{is_movable},
        sensor_detectability{sensor_detectability} {}
  explicit EntitySetup(bool zero_init, bool is_collision_detectable, bool is_movable,
                       prescan::api::types::SensorDetectability sensor_detectability)
      : position{zero_init},
        orientation{zero_init},
        cog_offset{zero_init},
        is_collision_detectable{is_collision_detectable},
        is_movable{is_movable},
        sensor_detectability{sensor_detectability} {}
  Position position;
  Orientation orientation;
  CenterOfGravityOffset cog_offset;
  bool is_collision_detectable;
  bool is_movable;
  prescan::api::types::SensorDetectability sensor_detectability;
};

std::ostream& operator<<(std::ostream& os, const Position& position);
std::ostream& operator<<(std::ostream& os, const Orientation& orientation);
std::ostream& operator<<(std::ostream& os, const Velocity& velocity);
std::ostream& operator<<(std::ostream& os, const Acceleration& acceleration);
std::ostream& operator<<(std::ostream& os, const AngularVelocity& angular_velocity);
std::ostream& operator<<(std::ostream& os, const CenterOfGravityOffset& cog_offset);
std::ostream& operator<<(std::ostream& os, const ModelState& model_state);
std::ostream& operator<<(std::ostream& os, const EntityState& model_state);
std::ostream& operator<<(std::ostream& os, const EntitySetup& entity_state);

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
template <>
struct fmt::formatter<symaware::CenterOfGravityOffset> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::ModelState> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::EntityState> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::EntitySetup> : fmt::ostream_formatter {};
