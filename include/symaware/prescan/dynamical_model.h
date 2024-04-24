/**
 * @file dynamical_model.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief DynamicalModel class
 */
#pragma once

#include <prescan/api/experiment/Experiment.hpp>
#include <prescan/sim/Simulation.hpp>
#include <prescan/sim/StateActuatorUnit.hpp>

namespace symaware {

// Forward declaration
class Entity;

class DynamicalModel {
 public:
  DynamicalModel();

  void initialise_entity(const Entity& entity);

  void registerUnit(prescan::api::experiment::Experiment& experiment, prescan::sim::ISimulation* simulation);
  void initialise(prescan::sim::ISimulation* simulation);
  void step(prescan::sim::ISimulation* simulation);
  void terminate(prescan::sim::ISimulation* simulation);

  const Entity& entity() const { return *entity_; }
  const prescan::sim::StateActuatorUnit& state() const { return *state_; }
  prescan::sim::StateActuatorUnit& m_state() const { return *state_; }

 private:
  const Entity* entity_;
  prescan::sim::StateActuatorUnit* state_;
};

}  // namespace symaware
