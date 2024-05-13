#include "symaware/prescan/model/simulation_model.h"

#include <iostream>
#include <prescan/api/Experiment.hpp>
#include <prescan/sim/Simulation.hpp>
#include <stdexcept>

namespace symaware {

SimulationModel::SimulationModel(const Environment& environment)
    : environment_{environment}, on_pre_step_{nullptr}, on_post_step_{nullptr} {};

void SimulationModel::registerSimulationUnits(const prescan::api::experiment::Experiment& experiment,
                                              prescan::sim::ISimulation* simulation) {
  for (const auto& [name, entity] : environment_.entities()) entity->registerUnit(experiment, simulation);
};

void SimulationModel::initialize(prescan::sim::ISimulation* simulation) {
  for (const auto& [name, entity] : environment_.entities()) entity->initialise(simulation);
};

void SimulationModel::step(prescan::sim::ISimulation* simulation) {
  if (on_pre_step_ != nullptr) on_pre_step_();
  for (const auto& [name, entity] : environment_.entities()) entity->step(simulation);
  if (on_post_step_ != nullptr) on_post_step_();
};

void SimulationModel::terminate(prescan::sim::ISimulation* simulation) {
  for (const auto& [name, entity] : environment_.entities()) entity->terminate(simulation);
};

}  // namespace symaware
