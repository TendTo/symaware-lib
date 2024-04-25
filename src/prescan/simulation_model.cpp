#include "symaware/prescan/simulation_model.h"

#include <iostream>
#include <prescan/api/Experiment.hpp>
#include <prescan/sim/Simulation.hpp>
#include <stdexcept>

namespace symaware {

SimulationModel::SimulationModel(const Environment& environment) : environment_{environment} {};

void SimulationModel::registerSimulationUnits(const prescan::api::experiment::Experiment& experiment,
                                              prescan::sim::ISimulation* simulation) {
  for (Entity* const entity : environment_.entities()) entity->registerUnit(experiment, simulation);
};

void SimulationModel::initialize(prescan::sim::ISimulation* simulation) {
  for (Entity* const entity : environment_.entities()) entity->initialise(simulation);
};

void SimulationModel::step(prescan::sim::ISimulation* simulation) {
  for (Entity* const entity : environment_.entities()) entity->step(simulation);
};

void SimulationModel::terminate(prescan::sim::ISimulation* simulation) {
  for (Entity* const entity : environment_.entities()) entity->terminate(simulation);
};

}  // namespace symaware