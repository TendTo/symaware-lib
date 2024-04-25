#include "symaware/prescan/simulation.h"

#include <prescan/sim/ManualSimulation.hpp>
#include <prescan/sim/Simulation.hpp>

#include "symaware/prescan/experiment_guard.h"
#include "symaware/util/exception.h"

namespace symaware {

Simulation::Simulation(const Environment& environment)
    : is_initialised_{false}, environment_{environment}, model_{environment}, simulation_{&model_} {}

void Simulation::run(double seconds) {
  if (is_initialised_) SYMAWARE_RUNTIME_ERROR("Simulation is already initialised. Cannot run again.");
  ExperimentGuard guard{const_cast<prescan::api::experiment::Experiment&>(environment_.experiment())};
  is_initialised_ = true;
  simulation_.run(environment_.experiment(), seconds);
  is_initialised_ = false;
}

void Simulation::step() {
  if (!is_initialised_) initialise();
  simulation_.step();
}

void Simulation::initialise() {
  ExperimentGuard guard{const_cast<prescan::api::experiment::Experiment&>(environment_.experiment())};
  simulation_.initialize(environment_.experiment());
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
