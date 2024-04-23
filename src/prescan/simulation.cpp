#include "symaware/prescan/simulation.h"

#include <prescan/sim/ManualSimulation.hpp>
#include <prescan/sim/Simulation.hpp>

#include "symaware/prescan/experiment_guard.h"
#include "symaware/util/exception.h"

namespace symaware {

Simulation::Simulation(const Environment& environment, prescan::sim::ISimulationModel& simulation_model)
    : is_initialised_{false}, experiment_{environment.experiment()}, simulation_{&simulation_model} {}
Simulation::Simulation(const prescan::api::experiment::Experiment experiment,
                       prescan::sim::ISimulationModel& simulation_model)
    : is_initialised_{false}, experiment_{std::move(experiment)}, simulation_{&simulation_model} {}

void Simulation::run(double seconds) {
  if (is_initialised_) SYMAWARE_RUNTIME_ERROR("Simulation is already initialised. Cannot run again.");
  ExperimentGuard guard{experiment_};
  is_initialised_ = true;
  simulation_.run(experiment_, seconds);
  is_initialised_ = false;
}

void Simulation::step() {
  if (!is_initialised_) initialise();
  simulation_.step();
}

void Simulation::initialise() {
  ExperimentGuard guard{experiment_};
  simulation_.initialize(experiment_);
  is_initialised_ = true;
}

void Simulation::terminate() {
  simulation_.terminate();
  is_initialised_ = false;
}

void Simulation::setLogLever(const prescan::sim::ISimulationLogger::LogLevel log_level) {
  simulation_.setLogLevel(log_level);
}

}  // namespace symaware
