#include "symaware/prescan/simulation_model.h"

#include <iostream>
#include <prescan/api/Experiment.hpp>
#include <prescan/sim/Simulation.hpp>
#include <stdexcept>

namespace symaware {

const double min_vel = -50;
const double max_vel = 50;
double multiplier = 1.0;

SimulationModel::SimulationModel(const std::vector<std::string>& controllable_agents)
    : controllable_agents_(controllable_agents){};

void SimulationModel::registerSimulationUnits(const prescan::api::experiment::Experiment& experiment,
                                              prescan::sim::ISimulation* simulation) {
  try {
    for (const auto& agent : controllable_agents_) {
      prescan::api::types::WorldObject obj = experiment.getObjectByName<prescan::api::types::WorldObject>(agent);
      std::cout << "Object " << agent << " registered to the simulation " << obj << std::endl;
      egoStateUnit_ = prescan::sim::registerUnit<prescan::sim::StateActuatorUnit>(simulation, obj);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    std::terminate();
  }
};
void SimulationModel::initialize(prescan::sim::ISimulation* simulation) {
  egoStateUnit_->stateActuatorInput().VelocityX = 36;
};

void SimulationModel::step(prescan::sim::ISimulation* simulation) {
  if (egoStateUnit_->stateActuatorInput().VelocityX > max_vel) {
    multiplier *= -1.0;
    egoStateUnit_->stateActuatorInput().VelocityX = max_vel;
  } else if (egoStateUnit_->stateActuatorInput().VelocityX < min_vel) {
    multiplier *= -1.0;
    egoStateUnit_->stateActuatorInput().VelocityX = min_vel;
  }

  egoStateUnit_->stateActuatorInput().VelocityX += multiplier;
};
void SimulationModel::terminate(prescan::sim::ISimulation* simulation) {
  // std::cout << "Simulation terminated" << std::endl;
};

}  // namespace symaware