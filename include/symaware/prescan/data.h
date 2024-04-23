/**
 * @file data.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Data structures
 */
#pragma once

namespace symaware {

struct Position {
  double x;
  double y;
  double z;
};

struct Orientation {
  double roll;
  double pitch;
  double yaw;
};

}  // namespace symaware
