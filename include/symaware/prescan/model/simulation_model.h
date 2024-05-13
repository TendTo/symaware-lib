/**
 * @file simulation_model.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief SimulationModel class
 */
#pragma once

#include <functional>
#include <prescan/sim/ISimulationModel.hpp>
#include <string>
#include <vector>

#include "symaware/prescan/entity.h"
#include "symaware/prescan/environment.h"

namespace symaware {

class SimulationModel : public prescan::sim::ISimulationModel {
 public:
  SimulationModel(const Environment& environment);
  void registerSimulationUnits(const prescan::api::experiment::Experiment& experiment,
                               prescan::sim::ISimulation* simulation) override;
  void initialize(prescan::sim::ISimulation* simulation) override;
  void step(prescan::sim::ISimulation* simulation) override;
  void terminate(prescan::sim::ISimulation* simulation) override;

  void setOnPreStep(const std::function<void()>& callback) { on_pre_step_ = callback; }
  void setOpPostStep(const std::function<void()>& callback) { on_post_step_ = callback; }
  const std::function<void()>& on_pre_step() { return on_pre_step_; }
  const std::function<void()>& on_post_step() { return on_post_step_; }

 private:
  const Environment& environment_;
  std::function<void()> on_pre_step_;
  std::function<void()> on_post_step_;
};

}  // namespace symaware
