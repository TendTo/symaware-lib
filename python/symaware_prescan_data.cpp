#include "symaware/prescan/data.h"
#include "symaware_prescan.h"

namespace py = pybind11;

void init_data(py::module_ &m) {
  py::enum_<symaware::Gear>(m, "Gear")
      .value("Forward", symaware::Gear::Forward)
      .value("Neutral", symaware::Gear::Neutral)
      .value("Reverse", symaware::Gear::Reverse)
      .value("Undefined", symaware::Gear::Undefined)
      .export_values();
  py::class_<symaware::Position>(m, "Position")
      .def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("x", &symaware::Position::x)
      .def_readwrite("y", &symaware::Position::y)
      .def_readwrite("z", &symaware::Position::z)
      .def("__repr__", REPR_LAMBDA(symaware::Position));
  py::class_<symaware::Orientation>(m, "Orientation")
      .def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("roll"), py::arg("pitch"), py::arg("yaw"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("roll", &symaware::Orientation::roll)
      .def_readwrite("pitch", &symaware::Orientation::pitch)
      .def_readwrite("yaw", &symaware::Orientation::yaw)
      .def("__repr__", REPR_LAMBDA(symaware::Orientation));
  py::class_<symaware::Velocity>(m, "Velocity")
      .def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("x", &symaware::Velocity::x)
      .def_readwrite("y", &symaware::Velocity::y)
      .def_readwrite("z", &symaware::Velocity::z)
      .def("__repr__", REPR_LAMBDA(symaware::Velocity));
  py::class_<symaware::Acceleration>(m, "Acceleration")
      .def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("x", &symaware::Acceleration::x)
      .def_readwrite("y", &symaware::Acceleration::y)
      .def_readwrite("z", &symaware::Acceleration::z)
      .def("__repr__", REPR_LAMBDA(symaware::Acceleration));
  py::class_<symaware::AngularVelocity>(m, "AngularVelocity")
      .def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("roll"), py::arg("pitch"), py::arg("yaw"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("roll", &symaware::AngularVelocity::roll)
      .def_readwrite("pitch", &symaware::AngularVelocity::pitch)
      .def_readwrite("yaw", &symaware::AngularVelocity::yaw)
      .def("__repr__", REPR_LAMBDA(symaware::AngularVelocity));
}
