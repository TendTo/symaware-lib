#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <iostream>

#include "symaware/prescan/sensor.h"
#include "symaware_prescan.h"

namespace py = pybind11;

void init_sensor(py::module_& m) {
  py::class_<symaware::Sensor>(m, "_Sensor")
      .def(py::init<symaware::SensorType, bool>(), py::arg("sensor_type"), py::arg("existing") = false)
      .def(py::init([](symaware::SensorType sensor_type, py::array_t<double> setup, bool existing) {
        std::vector<double> setup_vector;
        setup_vector.reserve(setup.size());
        for (int i = 0; i < setup.size(); i++) setup_vector.push_back(setup.at(i));
        return symaware::Sensor{sensor_type, setup_vector, existing};
      }))
      .def("create_sensor", &symaware::Sensor::createSensor, py::arg("object"), py::arg("id"))
      .def("register_unit", &symaware::Sensor::registerUnit, py::arg("object"), py::arg("experiment"),
           py::arg("simulation"))
      .def("initialise", &symaware::Sensor::initialise, py::arg("simulation"))
      .def("step", &symaware::Sensor::step, py::arg("simulation"))
      .def("terminate", &symaware::Sensor::terminate, py::arg("simulation"))

      .def_property_readonly("sensor_type", &symaware::Sensor::sensor_type)
      .def_property_readonly("setup", &symaware::Sensor::sensor_type)
      .def_property_readonly("state", &symaware::Sensor::sensor_type);
}
