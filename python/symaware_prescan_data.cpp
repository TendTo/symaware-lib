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

  py::class_<symaware::Position> class_position = py::class_<symaware::Position>(m, "Position");
  py::class_<symaware::Orientation> class_orientation = py::class_<symaware::Orientation>(m, "Orientation");
  py::class_<symaware::Velocity> class_velocity = py::class_<symaware::Velocity>(m, "Velocity");
  py::class_<symaware::Acceleration> class_acceleration = py::class_<symaware::Acceleration>(m, "Acceleration");
  py::class_<symaware::AngularVelocity> class_angular_velocity =
      py::class_<symaware::AngularVelocity>(m, "AngularVelocity");
  py::class_<symaware::CenterOfGravityOffset> class_center_of_gravity_offset =
      py::class_<symaware::CenterOfGravityOffset>(m, "CenterOfGravityOffset");

  class_position.def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("x", &symaware::Position::x)
      .def_readwrite("y", &symaware::Position::y)
      .def_readwrite("z", &symaware::Position::z)
      .def("__repr__", REPR_LAMBDA(symaware::Position));

  class_orientation.def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("roll"), py::arg("pitch"), py::arg("yaw"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("roll", &symaware::Orientation::roll)
      .def_readwrite("pitch", &symaware::Orientation::pitch)
      .def_readwrite("yaw", &symaware::Orientation::yaw)
      .def("__repr__", REPR_LAMBDA(symaware::Orientation));

  class_velocity.def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("x", &symaware::Velocity::x)
      .def_readwrite("y", &symaware::Velocity::y)
      .def_readwrite("z", &symaware::Velocity::z)
      .def("__repr__", REPR_LAMBDA(symaware::Velocity));

  class_acceleration.def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("x", &symaware::Acceleration::x)
      .def_readwrite("y", &symaware::Acceleration::y)
      .def_readwrite("z", &symaware::Acceleration::z)
      .def("__repr__", REPR_LAMBDA(symaware::Acceleration));

  class_angular_velocity.def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("roll"), py::arg("pitch"), py::arg("yaw"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("roll", &symaware::AngularVelocity::roll)
      .def_readwrite("pitch", &symaware::AngularVelocity::pitch)
      .def_readwrite("yaw", &symaware::AngularVelocity::yaw)
      .def("__repr__", REPR_LAMBDA(symaware::AngularVelocity));

  class_center_of_gravity_offset.def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("x", &symaware::CenterOfGravityOffset::x)
      .def_readwrite("y", &symaware::CenterOfGravityOffset::y)
      .def_readwrite("z", &symaware::CenterOfGravityOffset::z)
      .def("__repr__", REPR_LAMBDA(symaware::CenterOfGravityOffset));
}
