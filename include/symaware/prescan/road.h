/**
 * @file road.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Road class.
 */
#pragma once

#include <limits>
#include <prescan/api/Experiment.hpp>
#include <prescan/api/Roads.hpp>

#include "symaware/prescan/environment.h"

namespace symaware {

class Road {
 public:
  Road(Environment& environment);
  Road(prescan::api::experiment::Experiment& experiment);
  Road(prescan::api::roads::types::Road road);

  Road& addCurveSection(double length, double curvature) {
    road_.addArcSection(length, curvature);
    return *this;
  }
  Road& addCubicPolynomialSection(double length, double a, double b, double c, double d) {
    road_.addCubicPolynomialSection(length, a, b, c, d);
    return *this;
  }
  Road& addLane(prescan::api::roads::types::RoadSideType road_side, double width,
                prescan::api::roads::types::LaneType lane_type = prescan::api::roads::types::LaneType::LaneTypeDriving,
                double start_offset = 0.0, double end_offset = std::numeric_limits<double>::infinity()) {
    prescan::api::roads::types::Lane lane{road_.addLane(road_side, width, start_offset, end_offset)};
    lane.setType(lane_type);
    // TODO: handle markers
    // lane.getLaneMarker(prescan::api::roads::types::LaneSideType::LaneSideTypeInner).
    return *this;
  }
  Road& addParametricCubicPolynomialSection(double length, double aU, double bU, double cU, double dU, double aV,
                                            double bV, double cV, double dV,
                                            prescan::api::roads::types::ParameterRange parameterRange) {
    road_.addParametricCubicPolynomialSection(length, aU, bU, cU, dU, aV, bV, cV, dV, parameterRange);
    return *this;
  }
  Road& addParkingSpace(
      double length, double width, double yaw = 0,
      prescan::api::roads::types::RoadSideType road_side = prescan::api::roads::types::RoadSideType::RoadSideTypeLeft,
      double side_offset = 0, double offset = 0) {
    prescan::api::roads::types::ParkingSpace parking_space{road_.addParkingSpace()};
    parking_space.roadCoordinates().setRoadSide(road_side);
    parking_space.roadCoordinates().setSideOffset(side_offset);
    parking_space.roadCoordinates().setSOffset(offset);
    parking_space.setAsRectangle(length, width);
    parking_space.setYaw(yaw);
    return *this;
  }
  Road& addSpiralSection(double length, double startCurvature, double endCurvature) {
    road_.addSpiralSection(length, startCurvature, endCurvature);
    return *this;
  }
  Road& addStraightSection(double length) {
    road_.addStraightSection(length);
    return *this;
  }
  Road& setSpeedLimitProfile(double value, double start_offset = 0.0,
                             double end_offset = std::numeric_limits<double>::infinity()) {
    road_.speedLimitProfile().setValue(value, start_offset, end_offset);
    return *this;
  }
  Road& setTrafficSide(prescan::api::roads::types::TrafficSide traffic_side) {
    road_.setTrafficSide(traffic_side);
    return *this;
  }
  Road& setAsphaltColor(double r, double g, double b) {
    road_.asphalt().color().setRGB(r, g, b);
    return *this;
  }
  Road& setAsphaltType(prescan::api::roads::types::AsphaltType asphalt_type) {
    road_.asphalt().setType(asphalt_type);
    return *this;
  }
  Road& setAsphaltTextureScale(double texture_scale) {
    road_.asphalt().setTextureScale(texture_scale);
    return *this;
  }
  Road& setAsphaltTone(prescan::api::roads::types::AsphaltTone tone) {
    road_.asphalt().setTone(tone);
    return *this;
  }
  Road& setPosition(const Position& position) {
    road_.pose().position().setXYZ(position.x, position.y, position.z);
    return *this;
  }

  double length() const { return road_.length(); }
  const prescan::api::roads::types::Road& road() const { return road_; }

 private:
  prescan::api::roads::types::Road road_;  ///< Road object in the experiment
};

}  // namespace symaware
