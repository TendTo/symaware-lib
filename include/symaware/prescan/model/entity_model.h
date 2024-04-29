/**
 * @file entity_model.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief EntityModel class
 */
#pragma once

#include <prescan/api/experiment/Experiment.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/AmesimVehicleDynamicsUnit.hpp>
#include <prescan/sim/Simulation.hpp>
#include <prescan/sim/StateActuatorUnit.hpp>

#include "symaware/prescan/data.h"

namespace symaware {

class EntityModel {
 public:
  /**
   * @brief Construct a new Dynamical Model object with an initial model state.
   * @param state initial model state
   */
  explicit EntityModel();

  /**
   * @brief Initialise the model by assigning the object in the simulation.
   * @param object simulation object this model will control
   */
  virtual void initialiseObject(prescan::api::experiment::Experiment& experiment,
                                prescan::api::types::WorldObject object);

  /**
   * @brief Register the unit inside the @p simulaiton.
   *
   * Called at the beginning of the @p simulation.
   * Allows for the model to extract the @ref object_ from the @p simulation
   * and use it to register the @ref state_.
   * @param experiment experiment about to be run
   * @param simulation simulation that will run the experiment
   */
  virtual void registerUnit(const prescan::api::experiment::Experiment& experiment,
                            prescan::sim::ISimulation* simulation);
  /**
   * @brief Set the initial state of the model in the @p simulation.
   *
   * Called before the first step of the @p simulation.
   * @param simulation simulation that is about to run the experiment
   */
  virtual void initialise(prescan::sim::ISimulation* simulation);
  /**
   * @brief Set the state of the model in the @p simulation.
   *
   * Called at each step of the @p simulation.
   * @param simulation simulation that is running the experiment
   */
  virtual void step(prescan::sim::ISimulation* simulation);
  /**
   * @brief Dissaociate the model from the @p simulation.
   *
   * Called at the end of the @p simulation.
   * @param simulation simulation that has run the experiment
   */
  virtual void terminate(prescan::sim::ISimulation* simulation);

  const prescan::api::types::WorldObject& object() const { return object_; }
  const prescan::sim::StateActuatorUnit& state() const;

 protected:
  /**
   * @brief Use the @ref state_input_ to update the @ref state_ .
   *
   * Any `NaN` values in the @ref state_input_ are ignored
   * and the corresponding values in the @ref state_ are not changed.
   */
  virtual void updateState() = 0;

  prescan::api::types::WorldObject object_;  ///< The object that represents the entity in the simulation
  prescan::sim::StateActuatorUnit* state_;   ///< The state of the entity in the simulation
};

}  // namespace symaware
