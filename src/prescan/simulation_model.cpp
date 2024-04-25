#include "symaware/prescan/simulation_model.h"

#include <iostream>
#include <prescan/api/Experiment.hpp>
#include <prescan/sim/Simulation.hpp>
#include <stdexcept>

namespace symaware {

SimulationModel::SimulationModel(const Environment& environment) : entities_{environment.entities()} {};
SimulationModel::SimulationModel(const std::vector<Entity*>& entities) : entities_{entities} {};

void SimulationModel::registerSimulationUnits(const prescan::api::experiment::Experiment& experiment,
                                              prescan::sim::ISimulation* simulation) {
  for (Entity* const entity : entities_) entity->registerUnit(experiment, simulation);
};

void SimulationModel::initialize(prescan::sim::ISimulation* simulation) {
  for (Entity* const entity : entities_) entity->initialise(simulation);
};

void SimulationModel::step(prescan::sim::ISimulation* simulation) {
  for (Entity* const entity : entities_) entity->step(simulation);
};

void SimulationModel::terminate(prescan::sim::ISimulation* simulation) {
  for (Entity* const entity : entities_) entity->terminate(simulation);
};

}  // namespace symaware