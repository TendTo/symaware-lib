#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <iostream>

#include "symaware/prescan/model.h"
#include "symaware_prescan.h"

namespace py = pybind11;

class PyEntityModel : public symaware::EntityModel {
 public:
  using symaware::EntityModel::EntityModel;

  void initialiseObject(prescan::api::experiment::Experiment& experiment,
                        prescan::api::types::WorldObject object) override {
    PYBIND11_OVERRIDE_NAME(void, symaware::EntityModel, "initialise_object", initialiseObject, experiment, object);
  }
  void setInput(const std::vector<double>& input) override {
    PYBIND11_OVERRIDE_PURE_NAME(void, symaware::EntityModel, "set_input", setInput, input);
  }
  void updateInput(const std::vector<double>& input) override {
    PYBIND11_OVERRIDE_PURE_NAME(void, symaware::EntityModel, "update_input", updateInput, input);
  }
  void registerUnit(const prescan::api::experiment::Experiment& experiment,
                    prescan::sim::ISimulation* simulation) override {
    PYBIND11_OVERRIDE_NAME(void, symaware::EntityModel, "register_unit", registerUnit, experiment, simulation);
  }
  void initialise(prescan::sim::ISimulation* simulation) override {
    PYBIND11_OVERRIDE(void, symaware::EntityModel, initialise, simulation);
  }
  void step(prescan::sim::ISimulation* simulation) override {
    PYBIND11_OVERRIDE(void, symaware::EntityModel, step, simulation);
  }
  void terminate(prescan::sim::ISimulation* simulation) override {
    PYBIND11_OVERRIDE(void, symaware::EntityModel, terminate, simulation);
  }

 protected:
  void updateState() override { PYBIND11_OVERRIDE_PURE_NAME(void, symaware::EntityModel, "update_state", updateState); }
};

void init_model(py::module_& m) {
  py::class_<symaware::EntityModel, PyEntityModel>(m, "_EntityModel")
      .def(py::init<>())
      .def("set_object", &symaware::EntityModel::setObject, py::arg("object"), "Set the object of the model")
      .def("initialise_object", &symaware::EntityModel::initialiseObject, py::arg("experiment"), py::arg("object"),
           "Initialise the object of the model")
      .def("set_input", &symaware::EntityModel::setInput, py::arg("input"), "Set the input of the model")
      .def("update_input", &symaware::EntityModel::updateInput, py::arg("input"), "Update the input of the model")
      .def("register_unit", &symaware::EntityModel::registerUnit, py::arg("experiment"), py::arg("simulation"),
           "Register the unit of the model")
      .def("initialise", &symaware::EntityModel::initialise, py::arg("simulation"),
           "Called when the simulation is initialised")
      .def("step", &symaware::EntityModel::step, py::arg("simulation"), "Called at each simulation step")
      .def("terminate", &symaware::EntityModel::terminate, py::arg("simulation"),
           "Called when the simulation is terminated")

      .def_property_readonly("object", &symaware::EntityModel::object, "Internal WorldObject of the model");

  py::class_<symaware::TrackModel, symaware::EntityModel>(m, "_TrackModel")
      .def(py::init<>())
      .def(py::init<std::vector<symaware::Position>, double, double>(), py::arg("path"), py::arg("speed"),
           py::arg("tolerance"))
      .def("__repr__", REPR_LAMBDA(symaware::TrackModel));

  py::class_<symaware::AmesimDynamicalModel, symaware::EntityModel> amesimDynamicalModel =
      py::class_<symaware::AmesimDynamicalModel, symaware::EntityModel>(m, "_AmesimDynamicalModel");

  py::class_<symaware::AmesimDynamicalModel::Input>(amesimDynamicalModel, "Input")
      .def(py::init<>())
      .def(py::init<bool>(), py::arg("zero_init"))
      .def(py::init<double, double, double, symaware::Gear>(), py::arg("throttle"), py::arg("brake"),
           py::arg("steering_wheel_angle"), py::arg("gear"))
      .def(py::init([](py::array_t<double> a) {
             if (a.size() != 4) throw std::invalid_argument("Expected 4 elements");
             auto view = a.unchecked<1>();
             return symaware::AmesimDynamicalModel::Input{view(0), view(1), view(2),
                                                          static_cast<symaware::Gear>(view(3))};
           }),
           py::arg("array"))
      .def_readwrite("throttle", &symaware::AmesimDynamicalModel::Input::throttle)
      .def_readwrite("brake", &symaware::AmesimDynamicalModel::Input::brake)
      .def_readwrite("steering_wheel_angle", &symaware::AmesimDynamicalModel::Input::steering_wheel_angle)
      .def_readwrite("gear", &symaware::AmesimDynamicalModel::Input::gear)
      .def("__array__",
           [](const symaware::AmesimDynamicalModel::Input& self) -> py::array_t<double> {
             py::array_t a = py::array_t<double>({4}, {sizeof(double)});
             auto view = a.mutable_unchecked<1>();
             view(0) = self.throttle;
             view(1) = self.brake;
             view(2) = self.steering_wheel_angle;
             view(3) = static_cast<double>(self.gear);
             return a;
           })
      .def("__repr__", REPR_LAMBDA(symaware::AmesimDynamicalModel::Input));

  PYBIND11_NUMPY_DTYPE(symaware::AmesimDynamicalModel::Input, throttle, brake, steering_wheel_angle, gear);

  amesimDynamicalModel.def(py::init<>())
      .def(py::init<>())
      .def(py::init<symaware::AmesimDynamicalModel::Input>(), py::arg("initial_input"))
      .def(py::init<bool, symaware::AmesimDynamicalModel::Input>(), py::arg("is_flat_ground"), py::arg("initial_input"))
      .def("initialise_object", &symaware::AmesimDynamicalModel::initialiseObject, py::arg("experiment"),
           py::arg("object"))
      .def("register_unit", &symaware::AmesimDynamicalModel::registerUnit, py::arg("experiment"), py::arg("simulation"))
      .def(
          "set_input",
          [](symaware::AmesimDynamicalModel& model, const py::array_t<double>& input) {
            if (input.size() != 4) throw std::invalid_argument("Input must have 4 elements");
            std::vector<double> input_vector;
            input_vector.reserve(input.size());
            for (int i = 0; i < input.size(); i++) input_vector.push_back(input.at(i));
            model.setInput(input_vector);
          },
          py::arg("input"))
      .def(
          "update_input",
          [](symaware::AmesimDynamicalModel& model, const py::array_t<double>& input) {
            if (input.size() != 4) throw std::invalid_argument("Input must have 4 elements");
            std::vector<double> input_vector;
            input_vector.reserve(input.size());
            for (int i = 0; i < input.size(); i++) input_vector.push_back(input.at(i));
            model.updateInput(input_vector);
          },
          py::arg("input"))
      .def("set_input",
           py::overload_cast<symaware::AmesimDynamicalModel::Input>(&symaware::AmesimDynamicalModel::setInput),
           py::arg("input"))
      .def(
          "update_input",
          py::overload_cast<const symaware::AmesimDynamicalModel::Input&>(&symaware::AmesimDynamicalModel::updateInput),
          py::arg("input"))
      .def_property_readonly("is_flat_ground", &symaware::AmesimDynamicalModel::is_flat_ground,
                             "Whether the model is just assum everything is a flat ground")
      .def("__repr__", REPR_LAMBDA(symaware::AmesimDynamicalModel));

  py::class_<symaware::CustomDynamicalModel, symaware::EntityModel> customDynamicalModel =
      py::class_<symaware::CustomDynamicalModel, symaware::EntityModel>(m, "_CustomDynamicalModel");

  py::class_<symaware::CustomDynamicalModel::Input>(customDynamicalModel, "Input")
      .def(py::init<>())
      .def(py::init<bool>(), py::arg("zero_init"))
      .def(py::init<symaware::Position, symaware::Orientation, symaware::Acceleration, symaware::Velocity,
                    symaware::AngularVelocity>(),
           py::arg("position"), py::arg("orientation"), py::arg("acceleration"), py::arg("velocity"),
           py::arg("angular_velocity"))
      .def(py::init([](py::array_t<double> a) {
             if (a.size() != 15) throw std::invalid_argument("Expected 15 elements");
             auto view = a.unchecked<1>();
             return symaware::CustomDynamicalModel::Input{
                 symaware::Position{view(0), view(1), view(2)}, symaware::Orientation{view(3), view(4), view(5)},
                 symaware::Acceleration{view(6), view(7), view(8)}, symaware::Velocity{view(9), view(10), view(11)},
                 symaware::AngularVelocity{view(12), view(13), view(14)}};
           }),
           py::arg("array"))
      .def_readwrite("position", &symaware::CustomDynamicalModel::Input::position)
      .def_readwrite("orientation", &symaware::CustomDynamicalModel::Input::orientation)
      .def_readwrite("acceleration", &symaware::CustomDynamicalModel::Input::acceleration)
      .def_readwrite("velocity", &symaware::CustomDynamicalModel::Input::velocity)
      .def_readwrite("angular_velocity", &symaware::CustomDynamicalModel::Input::angular_velocity)
      .def("__array__",
           [](const symaware::CustomDynamicalModel::Input& self) -> py::array_t<double> {
             py::array_t a = py::array_t<double>({15}, {sizeof(double)});
             auto view = a.mutable_unchecked<1>();
             view(0) = self.position.x;
             view(1) = self.position.y;
             view(2) = self.position.z;
             view(3) = self.orientation.roll;
             view(4) = self.orientation.pitch;
             view(5) = self.orientation.yaw;
             view(6) = self.acceleration.x;
             view(7) = self.acceleration.y;
             view(8) = self.acceleration.z;
             view(9) = self.velocity.x;
             view(10) = self.velocity.y;
             view(11) = self.velocity.z;
             view(12) = self.angular_velocity.roll;
             view(13) = self.angular_velocity.pitch;
             view(14) = self.angular_velocity.yaw;
             return a;
           })
      .def("__repr__", REPR_LAMBDA(symaware::CustomDynamicalModel::Input));

  PYBIND11_NUMPY_DTYPE(symaware::CustomDynamicalModel::Input, position.x, position.y, position.z, orientation.roll,
                       orientation.pitch, orientation.yaw, acceleration.x, acceleration.y, acceleration.z, velocity.x,
                       velocity.y, velocity.z, angular_velocity.roll, angular_velocity.pitch, angular_velocity.yaw);

  customDynamicalModel.def(py::init<>())
      .def(py::init<symaware::CustomDynamicalModel::Input>(), py::arg("initial_input"))
      .def(
          "set_input",
          [](symaware::CustomDynamicalModel& model, const py::array_t<double>& input) {
            if (input.size() != 15) throw std::invalid_argument("Input must have 15 elements");
            std::vector<double> input_vector;
            input_vector.reserve(input.size());
            for (int i = 0; i < input.size(); i++) input_vector.push_back(input.at(i));
            model.setInput(input_vector);
          },
          py::arg("input"))
      .def(
          "update_input",
          [](symaware::CustomDynamicalModel& model, const py::array_t<double>& input) {
            if (input.size() != 15) throw std::invalid_argument("Input must have 15 elements");
            std::vector<double> input_vector;
            input_vector.reserve(input.size());
            for (int i = 0; i < input.size(); i++) input_vector.push_back(input.at(i));
            model.updateInput(input_vector);
          },
          py::arg("input"))
      .def("set_input",
           py::overload_cast<symaware::CustomDynamicalModel::Input>(&symaware::CustomDynamicalModel::setInput),
           py::arg("input"))
      .def(
          "update_input",
          py::overload_cast<const symaware::CustomDynamicalModel::Input&>(&symaware::CustomDynamicalModel::updateInput),
          py::arg("input"))
      .def_property_readonly("input", &symaware::CustomDynamicalModel::input)
      .def("__repr__", REPR_LAMBDA(symaware::CustomDynamicalModel));
}
