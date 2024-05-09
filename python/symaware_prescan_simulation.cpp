#include <iostream>

#include "symaware/prescan/simulation.h"
#include "symaware_prescan.h"

namespace py = pybind11;

void init_simulation(py::module_ &m) {
  py::class_<symaware::Simulation>(m, "_Simulation")
      .def(py::init<const symaware::Environment &>(), py::arg("environment"))
      .def("run", &symaware::Simulation::run, py::arg("seconds") = -1.0, "Run the simulation automatically.")
      .def("initialise", &symaware::Simulation::initialise, "Initialise the simulation.")
      .def("step", &symaware::Simulation::step, "Advance the simulation manually.")
      .def("terminate", &symaware::Simulation::terminate, "Terminate the simulation and clean up.")
      .def("set_log_level", &symaware::Simulation::setLogLevel, py::arg("log_level"),
           "Set the log level of the simulation logger.");
}
