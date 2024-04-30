#include <iostream>

#include "symaware/prescan/road.h"
#include "symaware_prescan.h"

namespace py = pybind11;

void init_road(py::module_ &m) {
  py::enum_<prescan::api::roads::types::RoadSideType>(m, "RoadSideType")
      .value("RoadSideTypeLeft", prescan::api::roads::types::RoadSideType::RoadSideTypeLeft)
      .value("RoadSideTypeRight", prescan::api::roads::types::RoadSideType::RoadSideTypeRight)
      .export_values();

  py::enum_<prescan::api::roads::types::LaneType>(m, "LaneType")
      .value("LaneTypeDriving", prescan::api::roads::types::LaneType::LaneTypeDriving)
      .value("LaneTypeBiking", prescan::api::roads::types::LaneType::LaneTypeBiking)
      .value("LaneTypeSideWalk", prescan::api::roads::types::LaneType::LaneTypeSideWalk)
      .export_values();

  py::enum_<prescan::api::roads::types::ParameterRange>(m, "ParameterRange")
      .value("ParamPolyRangeTypeArcLength", prescan::api::roads::types::ParameterRange::ParamPolyRangeTypeArcLength)
      .value("ParamPolyRangeTypeNormalized", prescan::api::roads::types::ParameterRange::ParamPolyRangeTypeNormalized)
      .export_values();

  py::enum_<prescan::api::roads::types::AsphaltType>(m, "AsphaltType")
      .value("AsphaltTypeColoredTexture", prescan::api::roads::types::AsphaltType::AsphaltTypeColoredTexture)
      .value("AsphaltTypeSingleColor", prescan::api::roads::types::AsphaltType::AsphaltTypeSingleColor)
      .value("AsphaltTypeStandard", prescan::api::roads::types::AsphaltType::AsphaltTypeStandard)
      .export_values();

  py::enum_<prescan::api::roads::types::TrafficSide>(m, "TrafficSide")
      .value("TrafficSideTypeLeftHandTraffic", prescan::api::roads::types::TrafficSide::TrafficSideTypeLeftHandTraffic)
      .value("TrafficSideTypeRightHandTraffic",
             prescan::api::roads::types::TrafficSide::TrafficSideTypeRightHandTraffic)
      .export_values();

  py::enum_<prescan::api::roads::types::LaneSideType>(m, "LaneSideType")
      .value("LaneSideTypeInner", prescan::api::roads::types::LaneSideType::LaneSideTypeInner)
      .value("LaneSideTypeOuter", prescan::api::roads::types::LaneSideType::LaneSideTypeOuter)
      .export_values();

  py::enum_<prescan::api::roads::types::AsphaltTone>(m, "AsphaltTone")
      .value("AsphaltToneDark", prescan::api::roads::types::AsphaltTone::AsphaltToneDark)
      .value("AsphaltToneDarker", prescan::api::roads::types::AsphaltTone::AsphaltToneDarker)
      .value("AsphaltToneLight", prescan::api::roads::types::AsphaltTone::AsphaltToneLight)
      .value("AsphaltToneLighter", prescan::api::roads::types::AsphaltTone::AsphaltToneLighter)
      .value("AsphaltToneStandard", prescan::api::roads::types::AsphaltTone::AsphaltToneStandard)
      .export_values();

  py::class_<symaware::Road> road = py::class_<symaware::Road>(m, "_Road");

  road.def(py::init<symaware::Environment &>(), py::arg("environment"))
      .def("add_curve_section", &symaware::Road::addCurveSection, "Add a curve section to the road", py::arg("length"),
           py::arg("curvature"))
      .def("add_cubic_polynomial_section", &symaware::Road::addCubicPolynomialSection,
           "Add a cubic polynomial section to the road", py::arg("length"), py::arg("a"), py::arg("b"), py::arg("c"),
           py::arg("d"))
      .def("add_lane", &symaware::Road::addLane, "Add a lane to the road", py::arg("road_side"), py::arg("width"),
           py::arg("lane_type"), py::arg("start_offset"), py::arg("end_offset"))
      .def("add_parametric_cubic_polynomial_section", &symaware::Road::addParametricCubicPolynomialSection,
           "Add a parametric cubic polynomial section to the road", py::arg("length"), py::arg("aU"), py::arg("bU"),
           py::arg("cU"), py::arg("dU"), py::arg("aV"), py::arg("bV"), py::arg("cV"), py::arg("dV"),
           py::arg("parameter_range"))
      .def("add_parking_space", &symaware::Road::addParkingSpace, "Add a parking space to the road", py::arg("length"),
           py::arg("width"), py::arg("yaw") = 0,
           py::arg("road_side") = prescan::api::roads::types::RoadSideType::RoadSideTypeLeft,
           py::arg("side_offset") = 0, py::arg("offset") = 0)
      .def("add_spiral_section", &symaware::Road::addSpiralSection, "Add a spiral section to the road",
           py::arg("length"), py::arg("start_curvature"), py::arg("end_curvature"))
      .def("add_straight_section", &symaware::Road::addStraightSection, "Add a straight section to the road",
           py::arg("length"))
      .def("set_speed_limit_profile", &symaware::Road::setSpeedLimitProfile, "Set the speed limit profile",
           py::arg("value"), py::arg("start_offset"), py::arg("end_offset"))
      .def("set_traffic_side", &symaware::Road::setTrafficSide, "Set the traffic side of the road",
           py::arg("traffic_side"))
      .def("set_asphalt_color", &symaware::Road::setAsphaltColor, "Set the asphalt color", py::arg("r"), py::arg("g"),
           py::arg("b"))
      .def("set_asphalt_texture_scale", &symaware::Road::setAsphaltTextureScale, "Set the asphalt texture scale",
           py::arg("texture_scale"))
      .def("set_asphalt_type", &symaware::Road::setAsphaltType, "Set the asphalt type", py::arg("asphalt_type"))
      .def("set_asphalt_tone", &symaware::Road::setAsphaltTone, "Set the asphalt tone", py::arg("tone"))
      .def("set_position", &symaware::Road::setPosition, "Set the position of the road", py::arg("position"))

      .def_property_readonly("length", &symaware::Road::length, "Get the length of the road")
      .def_property_readonly("road", &symaware::Road::road, "Get the road");
}
