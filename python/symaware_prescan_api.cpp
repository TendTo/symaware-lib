#include <prescan/api/Experiment.hpp>
#include <prescan/api/Roads.hpp>
#include <prescan/api/Viewer.hpp>
#include <prescan/api/types/WindowSettings.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/ISimulationLogger.hpp>

#include "symaware/prescan/data.h"
#include "symaware_prescan.h"

namespace py = pybind11;

void init_api(py::module_& m) {
  py::enum_<prescan::sim::ISimulationLogger::LogLevel>(m, "LogLevel")
      .value("LogLevelClean", prescan::sim::ISimulationLogger::LogLevel::LogLevelClean)
      .value("LogLevelCrawl", prescan::sim::ISimulationLogger::LogLevel::LogLevelCrawl)
      .value("LogLevelCritical", prescan::sim::ISimulationLogger::LogLevel::LogLevelCritical)
      .value("LogLevelDebug", prescan::sim::ISimulationLogger::LogLevel::LogLevelDebug)
      .value("LogLevelError", prescan::sim::ISimulationLogger::LogLevel::LogLevelError)
      .value("LogLevelInfo", prescan::sim::ISimulationLogger::LogLevel::LogLevelInfo)
      .value("LogLevelInherit", prescan::sim::ISimulationLogger::LogLevel::LogLevelInherit)
      .value("LogLevelNotice", prescan::sim::ISimulationLogger::LogLevel::LogLevelNotice)
      .value("LogLevelOff", prescan::sim::ISimulationLogger::LogLevel::LogLevelOff)
      .value("LogLevelWarning", prescan::sim::ISimulationLogger::LogLevel::LogLevelWarning)
      .export_values();

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

  py::enum_<prescan::api::types::SensorDetectability>(m, "SensorDetectability")
      .value("SensorDetectabilityDetectable", prescan::api::types::SensorDetectability::SensorDetectabilityDetectable)
      .value("SensorDetectabilityInvisible", prescan::api::types::SensorDetectability::SensorDetectabilityInvisible)
      .value("SensorDetectabilityOccluding", prescan::api::types::SensorDetectability::SensorDetectabilityOccluding)
      .export_values();

  py::enum_<prescan::api::types::SkyLightPollution>(m, "SkyLightPollution")
      .value("SkyLightPollutionBrightSuburban", prescan::api::types::SkyLightPollution::SkyLightPollutionBrightSuburban)
      .value("SkyLightPollutionCity", prescan::api::types::SkyLightPollution::SkyLightPollutionCity)
      .value("SkyLightPollutionDarkSite", prescan::api::types::SkyLightPollution::SkyLightPollutionDarkSite)
      .value("SkyLightPollutionInnerCity", prescan::api::types::SkyLightPollution::SkyLightPollutionInnerCity)
      .value("SkyLightPollutionNone", prescan::api::types::SkyLightPollution::SkyLightPollutionNone)
      .value("SkyLightPollutionRural", prescan::api::types::SkyLightPollution::SkyLightPollutionRural)
      .value("SkyLightPollutionRuralSuburban", prescan::api::types::SkyLightPollution::SkyLightPollutionRuralSuburban)
      .value("SkyLightPollutionSuburban", prescan::api::types::SkyLightPollution::SkyLightPollutionSuburban)
      .value("SkyLightPollutionSuburbanUrban", prescan::api::types::SkyLightPollution::SkyLightPollutionSuburbanUrban)
      .export_values();

  py::class_<prescan::api::experiment::Experiment>(m, "_Experiment")
      .def_static("create_experiment", &prescan::api::experiment::createExperiment)
      .def_static("load_experiment_from_file", &prescan::api::experiment::loadExperimentFromFile, py::arg("filename"))
      .def("object_types", &prescan::api::experiment::Experiment::objectTypes);

  py::class_<prescan::api::viewer::Viewer>(m, "_Viewer")
      .def_static("create_viewer", &prescan::api::viewer::createViewer, py::arg("experiment"))
      .def("remove", &prescan::api::viewer::Viewer::remove)
      .def("window_settings", &prescan::api::viewer::Viewer::windowSettings);

  py::class_<prescan::api::types::WindowSettings>(m, "_WindowSettings")
      .def_property("always_on_top", &prescan::api::types::WindowSettings::alwaysOnTop,
                    &prescan::api::types::WindowSettings::setAlwaysOnTop)
      .def_property("fullscreen", &prescan::api::types::WindowSettings::fullscreen,
                    &prescan::api::types::WindowSettings::setFullscreen)
      .def_property("height", &prescan::api::types::WindowSettings::height,
                    &prescan::api::types::WindowSettings::setHeight)
      .def_property("width", &prescan::api::types::WindowSettings::width,
                    &prescan::api::types::WindowSettings::setWidth)
      .def_property("origin_x", &prescan::api::types::WindowSettings::originX,
                    &prescan::api::types::WindowSettings::setOriginX)
      .def_property("origin_y", &prescan::api::types::WindowSettings::originY,
                    &prescan::api::types::WindowSettings::setOriginY)
      .def_property("screen_id", &prescan::api::types::WindowSettings::screenId,
                    &prescan::api::types::WindowSettings::setScreenId)
      .def_property("visualization_frequency", &prescan::api::types::WindowSettings::visualizationFrequency,
                    &prescan::api::types::WindowSettings::setVisualizationFrequency)
      .def_property("window_decoration", &prescan::api::types::WindowSettings::windowDecoration,
                    &prescan::api::types::WindowSettings::setWindowDecoration);

  py::class_<prescan::api::types::WorldObject>(m, "_WorldObject")
      .def("remove", prescan::api::types::WorldObject::remove)
      .def_property(
          "position",
          [](const prescan::api::types::WorldObject& self) {
            return symaware::Position{self.pose().position().x(), self.pose().position().y(),
                                      self.pose().position().z()};
          },
          [](prescan::api::types::WorldObject& self, const symaware::Position& position) {
            self.pose().position().setXYZ(position.x, position.y, position.z);
          })
      .def_property(
          "orientation",
          [](const prescan::api::types::WorldObject& self) {
            return symaware::Orientation{self.pose().orientation().roll(), self.pose().orientation().pitch(),
                                         self.pose().orientation().yaw()};
          },
          [](prescan::api::types::WorldObject& self, const symaware::Orientation& orientation) {
            self.pose().orientation().setRPY(orientation.roll, orientation.pitch, orientation.yaw);
          })
      .def_property(
          "cog_offset",
          [](const prescan::api::types::WorldObject& self) {
            return symaware::Position{self.cogOffset().x(), self.cogOffset().y(), self.cogOffset().z()};
          },
          [](prescan::api::types::WorldObject& self, const symaware::Position& cog_offset) {
            self.cogOffset().setXYZ(cog_offset.x, cog_offset.y, cog_offset.z);
          })
      .def_property("movable", prescan::api::types::WorldObject::movable, prescan::api::types::WorldObject::setMovable)
      .def_property("collision_detectable", prescan::api::types::WorldObject::collisionDetectable,
                    prescan::api::types::WorldObject::setCollisionDetectable)
      .def_property("name", prescan::api::types::WorldObject::name, prescan::api::types::WorldObject::setName);
}
