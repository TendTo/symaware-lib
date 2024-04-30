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
      .def("set_object", &symaware::EntityModel::setObject, py::arg("object"))
      .def("initialise_object", &symaware::EntityModel::initialiseObject, py::arg("experiment"), py::arg("object"))
      .def("set_input", &symaware::EntityModel::setInput, py::arg("input"))
      .def("update_input", &symaware::EntityModel::updateInput, py::arg("input"))
      .def("register_unit", &symaware::EntityModel::registerUnit, py::arg("experiment"), py::arg("simulation"))
      .def("initialise", &symaware::EntityModel::initialise, py::arg("simulation"))
      .def("step", &symaware::EntityModel::step, py::arg("simulation"))
      .def("terminate", &symaware::EntityModel::terminate, py::arg("simulation"))

      .def_property_readonly("object", &symaware::EntityModel::object)
      .def_property_readonly("state", &symaware::EntityModel::state);

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
      .def_readwrite("throttle", &symaware::AmesimDynamicalModel::Input::throttle)
      .def_readwrite("brake", &symaware::AmesimDynamicalModel::Input::brake)
      .def_readwrite("steering_wheel_angle", &symaware::AmesimDynamicalModel::Input::steering_wheel_angle)
      .def_readwrite("gear", &symaware::AmesimDynamicalModel::Input::gear)
      .def("__repr__", REPR_LAMBDA(symaware::AmesimDynamicalModel::Input));

  PYBIND11_NUMPY_DTYPE(symaware::AmesimDynamicalModel::Input, throttle, brake, steering_wheel_angle, gear);

  amesimDynamicalModel.def(py::init<>())
      .def(py::init<>())
      .def(py::init<symaware::AmesimDynamicalModel::Input>(), py::arg("initial_input"))
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
      .def_readwrite("position", &symaware::CustomDynamicalModel::Input::position)
      .def_readwrite("orientation", &symaware::CustomDynamicalModel::Input::orientation)
      .def_readwrite("acceleration", &symaware::CustomDynamicalModel::Input::acceleration)
      .def_readwrite("velocity", &symaware::CustomDynamicalModel::Input::velocity)
      .def_readwrite("angular_velocity", &symaware::CustomDynamicalModel::Input::angular_velocity)
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
