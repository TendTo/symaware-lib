#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <iostream>

#include "symaware/prescan/model.h"
#include "symaware_prescan.h"

namespace py = pybind11;

class PyEntityModel : public symaware::EntityModel {
 public:
  using symaware::EntityModel::EntityModel;

  void createIfNotExists(prescan::api::experiment::Experiment& experiment) override {
    PYBIND11_OVERRIDE_NAME(void, symaware::EntityModel, "create_if_not_exists", createIfNotExists, experiment);
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
      .def(py::init<bool, bool>(), py::arg("existing"), py::arg("active"))
      .def("link_entity",
           py::overload_cast<const prescan::api::types::WorldObject&>(&symaware::EntityModel::linkEntity),
           py::arg("object"), "Link the model to the object")
      .def("link_entity", py::overload_cast<const symaware::Entity&>(&symaware::EntityModel::linkEntity),
           py::arg("entity"), "Link the model to the entity")
      .def("create_if_not_exists", &symaware::EntityModel::createIfNotExists, py::arg("experiment"),
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

      .def_property_readonly("existing", &symaware::EntityModel::existing,
                             "Whether the model was already present in the experiment");

  py::class_<symaware::TrackModel, symaware::EntityModel> track_model =
      py::class_<symaware::TrackModel, symaware::EntityModel>(m, "_TrackModel");

  py::class_<symaware::TrackModel::Setup>(track_model, "Setup")
      .def(py::init<>())
      .def(py::init<bool, bool, std::vector<symaware::Position>, double, double>(), py::arg("existing"),
           py::arg("active"), py::arg("path"), py::arg("speed"), py::arg("tolerance"))
      .def_readwrite("existing", &symaware::TrackModel::Setup::existing)
      .def_readwrite("active", &symaware::TrackModel::Setup::active)
      .def_readwrite("path", &symaware::TrackModel::Setup::path)
      .def_readwrite("speed", &symaware::TrackModel::Setup::speed)
      .def_readwrite("tolerance", &symaware::TrackModel::Setup::tolerance);

  py::class_<symaware::TrackModel::Input>(track_model, "Input")
      .def(py::init<>())
      .def(py::init<bool>(), py::arg("zero_init"))
      .def(py::init<double, double, double, double, double, double>(), py::arg("velocity_mutiplier"),
           py::arg("velocity_offset"), py::arg("acceleration_multiplier"), py::arg("acceleration_offset"),
           py::arg("distance_multiplier"), py::arg("distance_offset"))
      .def(py::init([](py::array_t<double> a) {
             if (a.size() != 6) throw std::invalid_argument("Expected 6 elements");
             auto view = a.unchecked<1>();
             return symaware::TrackModel::Input{view(0), view(1), view(2), view(3), view(4), view(5)};
           }),
           py::arg("array"))
      .def_readwrite("velocity_multiplier", &symaware::TrackModel::Input::velocity_multiplier)
      .def_readwrite("velocity_offset", &symaware::TrackModel::Input::velocity_offset)
      .def_readwrite("acceleration_multiplier", &symaware::TrackModel::Input::acceleration_multiplier)
      .def_readwrite("acceleration_offset", &symaware::TrackModel::Input::acceleration_offset)
      .def_readwrite("distance_multiplier", &symaware::TrackModel::Input::distance_multiplier)
      .def_readwrite("distance_offset", &symaware::TrackModel::Input::distance_offset)
      .def("__array__",
           [](const symaware::TrackModel::Input& self) -> py::array_t<double> {
             py::array_t a = py::array_t<double>({6}, {sizeof(double)});
             auto view = a.mutable_unchecked<1>();
             view(0) = self.velocity_multiplier;
             view(1) = self.velocity_offset;
             view(2) = self.acceleration_multiplier;
             view(3) = self.acceleration_offset;
             view(4) = self.distance_multiplier;
             view(5) = self.distance_offset;
             return a;
           })
      .def("__repr__", REPR_LAMBDA(symaware::TrackModel::Input));

  track_model.def(py::init<>())
      .def(py::init<const symaware::TrackModel::Setup&>(), py::arg("setup"))
      .def(
          "set_input",
          [](symaware::TrackModel& model, const py::array_t<double>& input) {
            if (input.size() != 6) throw std::invalid_argument("Input must have 6 elements");
            std::vector<double> input_vector;
            input_vector.reserve(input.size());
            for (int i = 0; i < input.size(); i++) input_vector.push_back(input.at(i));
            model.setInput(input_vector);
          },
          py::arg("input"))
      .def(
          "update_input",
          [](symaware::TrackModel& model, const py::array_t<double>& input) {
            if (input.size() != 6) throw std::invalid_argument("Input must have 6 elements");
            std::vector<double> input_vector;
            input_vector.reserve(input.size());
            for (int i = 0; i < input.size(); i++) input_vector.push_back(input.at(i));
            model.updateInput(input_vector);
          },
          py::arg("input"))
      .def("set_input", py::overload_cast<symaware::TrackModel::Input>(&symaware::TrackModel::setInput),
           py::arg("input"))
      .def("update_input", py::overload_cast<const symaware::TrackModel::Input&>(&symaware::TrackModel::updateInput),
           py::arg("input"))
      .def(
          "trajectory_poses",
          [](const symaware::TrackModel& self, std::size_t num_segments) -> py::array_t<double> {
            py::array_t a =
                py::array_t<double>({num_segments, static_cast<std::size_t>(6)}, {6 * sizeof(double), sizeof(double)});
            auto view = a.mutable_unchecked<2>();
            const std::vector<symaware::Pose> poses = self.trajectoryPoses(num_segments);
            for (std::size_t i = 0; i < poses.size(); i++) {
              view(i, 0) = poses[i].position.x;
              view(i, 1) = poses[i].position.y;
              view(i, 2) = poses[i].position.z;
              view(i, 3) = poses[i].orientation.roll;
              view(i, 4) = poses[i].orientation.pitch;
              view(i, 5) = poses[i].orientation.yaw;
            }
            return a;
          },
          py::arg("num_segments"))
      .def_property_readonly("trajectory_positions",
                             [](const symaware::TrackModel& self) -> py::array_t<double> {
                               py::array_t a =
                                   py::array_t<double>({self.trajectoryPositions().size(), static_cast<std::size_t>(3)},
                                                       {3 * sizeof(double), sizeof(double)});
                               auto view = a.mutable_unchecked<2>();
                               for (std::size_t i = 0; i < self.trajectoryPositions().size(); i++) {
                                 view(i, 0) = self.trajectoryPositions()[i].x;
                                 view(i, 1) = self.trajectoryPositions()[i].y;
                                 view(i, 2) = self.trajectoryPositions()[i].z;
                               }
                               return a;
                             })
      .def("__repr__", REPR_LAMBDA(symaware::TrackModel));

  py::class_<symaware::AmesimDynamicalModel, symaware::EntityModel> amesimDynamicalModel =
      py::class_<symaware::AmesimDynamicalModel, symaware::EntityModel>(m, "_AmesimDynamicalModel");

  py::class_<symaware::AmesimDynamicalModel::Setup>(amesimDynamicalModel, "Setup")
      .def(py::init<>())
      .def(py::init<bool, bool, bool, double>(), py::arg("existing"), py::arg("active"), py::arg("is_flat_ground"),
           py::arg("initial_velocity"))
      .def_readwrite("existing", &symaware::AmesimDynamicalModel::Setup::existing)
      .def_readwrite("active", &symaware::AmesimDynamicalModel::Setup::active)
      .def_readwrite("is_flat_ground", &symaware::AmesimDynamicalModel::Setup::is_flat_ground)
      .def_readwrite("initial_velocity", &symaware::AmesimDynamicalModel::Setup::initial_velocity);

  py::class_<symaware::AmesimDynamicalModel::Input>(amesimDynamicalModel, "Input")
      .def(py::init<>())
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
      .def(py::init<symaware::AmesimDynamicalModel::Input>(), py::arg("initial_input"))
      .def(py::init<const symaware::AmesimDynamicalModel::Setup&, symaware::AmesimDynamicalModel::Input>(),
           py::arg("setup"), py::arg("initial_input") = symaware::AmesimDynamicalModel::Input{false})
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
      .def_property_readonly("initial_velocity", &symaware::AmesimDynamicalModel::initial_velocity,
                             "Initial velocity of the model")
      .def("__repr__", REPR_LAMBDA(symaware::AmesimDynamicalModel));

  py::class_<symaware::CustomDynamicalModel, symaware::EntityModel> customDynamicalModel =
      py::class_<symaware::CustomDynamicalModel, symaware::EntityModel>(m, "_CustomDynamicalModel");

  py::class_<symaware::CustomDynamicalModel::Setup>(customDynamicalModel, "Setup")
      .def(py::init<>())
      .def(py::init<bool, bool>(), py::arg("existing"), py::arg("active"))
      .def_readwrite("existing", &symaware::CustomDynamicalModel::Setup::existing)
      .def_readwrite("active", &symaware::CustomDynamicalModel::Setup::active);

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
      .def(py::init<const symaware::CustomDynamicalModel::Setup&, symaware::CustomDynamicalModel::Input>(),
           py::arg("setup"), py::arg("initial_input") = symaware::CustomDynamicalModel::Input{false})
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
