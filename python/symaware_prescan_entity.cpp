#include <pybind11/numpy.h>

#include "symaware/prescan/entity.h"
#include "symaware_prescan.h"

namespace py = pybind11;

void init_entity(py::module_& m) {
  py::class_<symaware::Entity> entity = py::class_<symaware::Entity>(m, "_Entity");

  py::class_<symaware::Entity::Setup>(entity, "Setup")
      .def(py::init<>())
      .def(py::init<symaware::Position, symaware::Orientation, symaware::Position, bool, bool,
                    prescan::api::types::SensorDetectability>(),
           py::arg("position"), py::arg("orientation"), py::arg("cog_offset"), py::arg("is_collision_detectable"),
           py::arg("is_movable"), py::arg("sensor_detectability"))
      .def(py::init<bool, bool, bool, prescan::api::types::SensorDetectability>(), py::arg("zero_init"),
           py::arg("is_collision_detectable"), py::arg("is_movable"), py::arg("sensor_detectability"))
      .def_readwrite("position", &symaware::Entity::Setup::position)
      .def_readwrite("orientation", &symaware::Entity::Setup::orientation)
      .def_readwrite("cog_offset", &symaware::Entity::Setup::cog_offset)
      .def_readwrite("is_collision_detectable", &symaware::Entity::Setup::is_collision_detectable)
      .def_readwrite("is_movable", &symaware::Entity::Setup::is_movable)
      .def_readwrite("sensor_detectability", &symaware::Entity::Setup::sensor_detectability)
      .def("__repr__", REPR_LAMBDA(symaware::Entity::Setup));

  PYBIND11_NUMPY_DTYPE(symaware::Entity::Setup, position.x, position.y, position.z, orientation.roll, orientation.pitch,
                       orientation.yaw, cog_offset.x, cog_offset.y, cog_offset.z, is_collision_detectable, is_movable,
                       sensor_detectability);

  py::class_<symaware::Entity::State>(entity, "State")
      .def(py::init<>())
      .def(py::init<symaware::Position, symaware::Orientation, double, double>(), py::arg("position"),
           py::arg("orientation"), py::arg("velocity"), py::arg("yaw_rate"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def_readwrite("position", &symaware::Entity::State::position)
      .def_readwrite("orientation", &symaware::Entity::State::orientation)
      .def_readwrite("velocity", &symaware::Entity::State::velocity)
      .def_readwrite("yaw_rate", &symaware::Entity::State::yaw_rate)
      .def("__repr__", REPR_LAMBDA(symaware::Entity::State));

  PYBIND11_NUMPY_DTYPE(symaware::Entity::State, position.x, position.y, position.z, orientation.roll, orientation.pitch,
                       orientation.yaw, velocity, yaw_rate);

  entity
      .def(py::init<symaware::Environment::ObjectType, symaware::Entity::Setup, symaware::EntityModel*>(),
           py::arg("object_type"), py::arg("setup") = symaware::Entity::Setup{},
           py::arg("entity_model") = static_cast<symaware::EntityModel*>(nullptr))
      .def(py::init<const std::string&, symaware::Environment&, symaware::Entity::Setup, symaware::EntityModel*>(),
           py::arg("name"), py::arg("environment"), py::arg("setup") = symaware::Entity::Setup{},
           py::arg("entity_model") = static_cast<symaware::EntityModel*>(nullptr))

      .def("initialise_object", &symaware::Entity::initialiseObject, py::arg("experiment"), py::arg("object"))
      .def("register_unit", &symaware::Entity::registerUnit, py::arg("experiment"), py::arg("simulation"))
      .def("initialise", &symaware::Entity::initialise, py::arg("simulation"))
      .def("step", &symaware::Entity::step, py::arg("simulation"))
      .def("terminate", &symaware::Entity::terminate, py::arg("simulation"))

      .def_property_readonly("state", &symaware::Entity::state, "Get the current state of the entity")
      .def_property_readonly("type", &symaware::Entity::type, "Get the type of the entity")
      .def_property_readonly("object", &symaware::Entity::object, "Get the worldobject wrapped by the entity")
      .def_property_readonly("is_initialized", &symaware::Entity::is_initialized,
                             "Get whether the entity is initialized")
      .def("__repr__", REPR_LAMBDA(symaware::Entity));
}
