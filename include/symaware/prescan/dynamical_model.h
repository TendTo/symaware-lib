/**
 * @file dynamical_model.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief DynamicalModel class
 */
#pragma once

#include <prescan/api/experiment/Experiment.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/Simulation.hpp>
#include <prescan/sim/StateActuatorUnit.hpp>

#include "symaware/prescan/data.h"

namespace symaware {

class DynamicalModel {
 public:
 /**
  * @brief Construct a new Dynamical Model object with an initial model state.
  * @param state initial model state 
  */
  explicit DynamicalModel(ModelState state = ModelState{false});

  /**
   * @brief Initialise the model by assigning the object in the simulation.
   * @param object simulation object this model will control 
   */
  void initialiseObject(prescan::api::types::WorldObject object);
  /**
   * @brief Set the new model state of the model.
   * @param state model state to be set 
   */
  void setState(ModelState state);

  /**
   * @brief Register the unit inside the @p simulaiton.
   * 
   * Called at the beginning of the @p simulation.
   * Allows for the model to extract the @ref object_ from the @p simulation 
   * and use it to register the @ref state_.
   * @param experiment experiment about to be run
   * @param simulation simulation that will run the experiment
   */
  void registerUnit(prescan::api::experiment::Experiment& experiment, prescan::sim::ISimulation* simulation);
  /**
   * @brief Set the initial state of the model in the @p simulation.
   * 
   * Called before the first step of the @p simulation.
   * @param simulation simulation that is about to run the experiment
   */
  void initialise(prescan::sim::ISimulation* simulation);
  /**
   * @brief Set the state of the model in the @p simulation.
   * 
   * Called at each step of the @p simulation.
   * @param simulation simulation that is running the experiment
   */
  void step(prescan::sim::ISimulation* simulation);
  /**
   * @brief Dissaociate the model from the @p simulation.
   * 
   * Called at the end of the @p simulation.
   * @param simulation simulation that has run the experiment
   */
  void terminate(prescan::sim::ISimulation* simulation);

  const prescan::api::types::WorldObject& object() const { return object_; }
  const prescan::sim::StateActuatorUnit& state() const { return *state_; }
  prescan::sim::StateActuatorUnit& m_state() const { return *state_; }

 private:
  /**
   * @brief Use the @ref state_input_ to update the @ref state_ .
   *
   * Any `NaN` values in the @ref state_input_ are ignored
   * and the corresponding values in the @ref state_ are not changed.
   */
  void updateState();

  prescan::api::types::WorldObject object_;  ///< The object that represents the entity in the simulation
  prescan::sim::StateActuatorUnit* state_;   ///< The state of the entity in the simulation
  ModelState model_state_;                        ///< The model state of the entity that will be applied each step
};

}  // namespace symaware
