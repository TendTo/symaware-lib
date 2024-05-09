#include <pybind11/stl.h>

#include <iostream>

#include "symaware/prescan/entity.h"
#include "symaware/prescan/environment.h"
#include "symaware/prescan/road.h"
#include "symaware/util/exception.h"
#include "symaware_prescan.h"

namespace py = pybind11;

void init_environment(py::module_ &m) {
  py::class_<symaware::Environment> environment = py::class_<symaware::Environment>(m, "_Environment");
  environment.def(py::init<>())
      .def(py::init<const std::string &>(), py::arg("filename"))
      .def("set_weather", &symaware::Environment::setWeather, "Set the weather of the environment",
           py::arg_v("weather_type", symaware::WeatherType::SUNNY, "WeatherType.SUNNY"), py::arg("fog_visibility") = -1)
      .def("set_sky", &symaware::Environment::setSky, "Set the sky of the environment",
           py::arg_v("sky_type", symaware::SkyType::DAY, "SkyType.DAY"),
           py::arg_v("light_pollution", prescan::api::types::SkyLightPollution::SkyLightPollutionNone,
                     "SkyLightPollution.SkyLightPollutionNone"))
      .def("set_scheduler_frequencies", &symaware::Environment::setSchedulerFrequencies,
           "Set the scheduler frequencies of the environment", py::arg("simulation_frequency"),
           py::arg("integration_frequency"))
      .def("set_scheduler_speed", &symaware::Environment::setSchedulerSpeed,
           "Set the scheduler speed of the environment", py::arg("simulation_speed"), py::arg("ignore_frame_overrun"))
      .def("add_entity", py::overload_cast<symaware::Entity &>(&symaware::Environment::addEntity),
           "Add an entity to the environment", py::arg("entity"))
      .def("add_entity", py::overload_cast<const std::string &, symaware::Entity &>(&symaware::Environment::addEntity),
           "Collect an existing entity from the experiment", py::arg("name"), py::arg("entity"))
      .def("add_road", &symaware::Environment::addRoad, "Add a road to the environment",
           py::arg_v("position", symaware::Position{true}, "Position(true)"))
      .def("add_free_viewer", &symaware::Environment::addFreeViewer, "Add a free viewer in the environment")
      .def("remove_all_viewers", &symaware::Environment::removeAllViewers, "Remove all viewers from the environment")
      .def("import_open_drive_network", &symaware::Environment::importOpenDriveNetwork,
           "Import an OpenDrive network from a file", py::arg("filename"))
      .def("save_experiment", &symaware::Environment::saveExperiment, "Save the experiment to file",
           py::arg("filename"))

      .def_property_readonly("experiment", &symaware::Environment::experiment, "Get the experiment of the environment");
}
