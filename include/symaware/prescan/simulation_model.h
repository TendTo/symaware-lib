/**
 * @file simulation_model.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief SimulationModel class
 */
#pragma once

#include <prescan/sim/ISimulationModel.hpp>
#include <prescan/sim/StateActuatorUnit.hpp>
#include <string>
#include <vector>

#include "symaware/prescan/environment.h"

namespace symaware {

class SimulationModel : public prescan::sim::ISimulationModel {
 public:
  SimulationModel(std::vector<std::string> controllable_agents);
  SimulationModel(const Environment& environment);
  void registerSimulationUnits(const prescan::api::experiment::Experiment& experiment,
                               prescan::sim::ISimulation* simulation) override;
  void initialize(prescan::sim::ISimulation* simulation) override;
  void step(prescan::sim::ISimulation* simulation) override;
  void terminate(prescan::sim::ISimulation* simulation) override;

 private:
  const std::vector<std::string>& controllable_agents_;
  prescan::sim::StateActuatorUnit* egoStateUnit_{nullptr};
};

}  // namespace symaware
