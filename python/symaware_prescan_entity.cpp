#include <pybind11/numpy.h>

#include "symaware/prescan/entity.h"
#include "symaware/util/exception.h"
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
      .def(py::init([](py::array_t<double> a) {
             if (a.size() != 12) SYMAWARE_OUT_OF_RANGE_FMT("Expected 12 elements, got {}", a.size());

             auto view = a.unchecked<1>();
             prescan::api::types::SensorDetectability sensor_detectability;
             if (view(11) == prescan::api::types::SensorDetectability::SensorDetectabilityOccluding)
               sensor_detectability = prescan::api::types::SensorDetectability::SensorDetectabilityOccluding;
             else if (view(11) == prescan::api::types::SensorDetectability::SensorDetectabilityInvisible)
               sensor_detectability = prescan::api::types::SensorDetectability::SensorDetectabilityInvisible;
             else
               sensor_detectability = prescan::api::types::SensorDetectability::SensorDetectabilityDetectable;

             return symaware::Entity::Setup{symaware::Position{view(0), view(1), view(2)},
                                            symaware::Orientation{view(3), view(4), view(5)},
                                            symaware::Position{view(6), view(7), view(8)},
                                            view(9) != 0,
                                            view(10) != 0,
                                            sensor_detectability};
           }),
           py::arg("array"))
      .def_readwrite("position", &symaware::Entity::Setup::position)
      .def_readwrite("orientation", &symaware::Entity::Setup::orientation)
      .def_readwrite("cog_offset", &symaware::Entity::Setup::cog_offset)
      .def_readwrite("is_collision_detectable", &symaware::Entity::Setup::is_collision_detectable)
      .def_readwrite("is_movable", &symaware::Entity::Setup::is_movable)
      .def_readwrite("sensor_detectability", &symaware::Entity::Setup::sensor_detectability)
      .def("__array__",
           [](const symaware::Entity::Setup& self) -> py::array_t<double> {
             py::array_t a = py::array_t<double>({12}, {sizeof(double)});
             auto view = a.mutable_unchecked<1>();
             view(0) = self.position.x;
             view(1) = self.position.y;
             view(2) = self.position.z;
             view(3) = self.orientation.roll;
             view(4) = self.orientation.pitch;
             view(5) = self.orientation.yaw;
             view(6) = self.cog_offset.x;
             view(7) = self.cog_offset.y;
             view(8) = self.cog_offset.z;
             view(9) = self.is_collision_detectable;
             view(10) = self.is_movable;
             view(11) = self.sensor_detectability;
             return a;
           })
      .def("__repr__", REPR_LAMBDA(symaware::Entity::Setup));

  py::class_<symaware::Entity::State>(entity, "State")
      .def(py::init<>())
      .def(py::init<symaware::Position, symaware::Orientation, double, double>(), py::arg("position"),
           py::arg("orientation"), py::arg("velocity"), py::arg("yaw_rate"))
      .def(py::init<bool>(), py::arg("zero_init"))
      .def(py::init([](py::array_t<double> a) {
             if (a.size() != 8) SYMAWARE_OUT_OF_RANGE_FMT("Expected 8 elements, got {}", a.size());

             auto view = a.unchecked<1>();
             return symaware::Entity::State{symaware::Position{view(0), view(1), view(2)},
                                            symaware::Orientation{view(3), view(4), view(5)}, view(6), view(7)};
           }),
           py::arg("array"))
      .def_readwrite("position", &symaware::Entity::State::position)
      .def_readwrite("orientation", &symaware::Entity::State::orientation)
      .def_readwrite("velocity", &symaware::Entity::State::velocity)
      .def_readwrite("yaw_rate", &symaware::Entity::State::yaw_rate)
      .def("__array__",
           [](const symaware::Entity::State& self) -> py::array_t<double> {
             py::array_t a = py::array_t<double>({8}, {sizeof(double)});
             auto view = a.mutable_unchecked<1>();
             view(0) = self.position.x;
             view(1) = self.position.y;
             view(2) = self.position.z;
             view(3) = self.orientation.roll;
             view(4) = self.orientation.pitch;
             view(5) = self.orientation.yaw;
             view(6) = self.velocity;
             view(7) = self.yaw_rate;
             return a;
           })
      .def("__repr__", REPR_LAMBDA(symaware::Entity::State));

  entity
      .def(py::init<symaware::ObjectType, symaware::Entity::Setup, symaware::EntityModel*>(), py::arg("object_type"),
           py::arg("setup") = symaware::Entity::Setup{},
           py::arg("entity_model") = static_cast<symaware::EntityModel*>(nullptr))

      .def("add_sensor", &symaware::Entity::addSensor, py::arg("sensor"))
      .def("apply_setup", py::overload_cast<>(&symaware::Entity::applySetup))
      .def("apply_setup", py::overload_cast<symaware::Entity::Setup>(&symaware::Entity::applySetup), py::arg("setup"))
      .def("initialise_object", &symaware::Entity::initialiseObject, py::arg("experiment"), py::arg("object"))
      .def("register_unit", &symaware::Entity::registerUnit, py::arg("experiment"), py::arg("simulation"))
      .def("initialise", &symaware::Entity::initialise, py::arg("simulation"))
      .def("step", &symaware::Entity::step, py::arg("simulation"))
      .def("terminate", &symaware::Entity::terminate, py::arg("simulation"))

      .def_property_readonly("is_initialised", &symaware::Entity::is_initialised,
                             "Wether the world object has been initialised")
      .def_property_readonly("state", &symaware::Entity::state, "Get the current state of the entity")
      .def_property_readonly("setup", &symaware::Entity::setup, "Get the current initial setup of the entity")
      .def_property_readonly("type", &symaware::Entity::type, "Get the type of the entity")
      .def_property_readonly("object", &symaware::Entity::object, "Get the worldobject wrapped by the entity")
      .def("__repr__", REPR_LAMBDA(symaware::Entity));
}
