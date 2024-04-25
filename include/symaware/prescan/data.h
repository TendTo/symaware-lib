/**
 * @file data.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Data structures
 */
#pragma once

#include <limits>
#include <prescan/api/types/WorldObject.hpp>

static_assert(std::numeric_limits<double>::has_quiet_NaN, "IEEE 754 required");

namespace symaware {

struct Position {
  explicit Position(bool zero_init = true)
      : x{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        y{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        z{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double x;
  double y;
  double z;
};

struct Orientation {
  explicit Orientation(bool zero_init = true)
      : roll{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        pitch{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        yaw{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double roll;
  double pitch;
  double yaw;
};

struct Velocity {
  explicit Velocity(bool zero_init = true)
      : x{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        y{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        z{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double x;
  double y;
  double z;
};

struct Acceleration {
  explicit Acceleration(bool zero_init = true)
      : x{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        y{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        z{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double x;
  double y;
  double z;
};

struct AngularVelocity {
  explicit AngularVelocity(bool zero_init = true)
      : roll{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        pitch{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        yaw{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double roll;
  double pitch;
  double yaw;
};

struct CenterOfGravityOffset {
  explicit CenterOfGravityOffset(bool zero_init = true)
      : x{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        y{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
        z{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}
  double x;
  double y;
  double z;
};

struct ModelState {
  explicit ModelState(bool zero_init = true)
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
  Position position;
  Orientation orientation;
  CenterOfGravityOffset cog_offset;
  bool is_collision_detectable;
  bool is_movable;
  prescan::api::types::SensorDetectability sensor_detectability;
};

}  // namespace symaware
