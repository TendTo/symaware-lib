#include <iostream>

#include "symaware/prescan/simulation.h"
#include "symaware_prescan.h"

namespace py = pybind11;

void init_simulation(py::module_ &m) {
  py::class_<symaware::Simulation>(m, "_Simulation")
      .def(py::init<const symaware::Environment &>())
      .def("run", &symaware::Simulation::run, py::arg("seconds") = -1.0)
      .def("step", &symaware::Simulation::step)
      .def("terminate", &symaware::Simulation::terminate)
      .def("setLogLevel", &symaware::Simulation::setLogLevel, py::arg("log_level"));
}
