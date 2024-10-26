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

class Entity;  // Forward declaration

class EntityModel {
 public:
  /**
   * @brief Construct a new Dynamical Model object with an initial model state.
   * @param existing whether the dynamical model is already present in the experiment or shall be created
   * @param active whether the dynamical model will step in the simulation
   */
  explicit EntityModel(bool existing, bool active);

  /**
   * @brief Initialise the model by assigning the object in the simulation.
   *
   * The object is stored in @ref object_ .
   * @param object simulation object this model will control
   * @param experiment experiment about to be run
   */
  virtual void createIfNotExists(prescan::api::experiment::Experiment& experiment);

  /**
   * @brief Link the model to the entity represented by the @p object.
   *
   * The bot the entity and this model must exist in the simulation.
   * @warning This method will only create the link model -> entity, but not viceversa.
   * Add the model to the Entity object to achieve a full link.
   * @param object_name name of the entity in the simulation
   */
  void linkEntity(const prescan::api::types::WorldObject& object);
  /**
   * @brief Link the model to the @p entity.
   *
   * The bot the entity and this model must exist in the simulation.
   * @warning This method will only create the link model -> entity, but not viceversa.
   * Add the model to the Entity object to achieve a full link.
   * @param object_name name of the entity in the simulation
   */
  void linkEntity(const Entity& entity);

  /**
   * @brief Set the new control input of the model.
   *
   * The internal mapping between the vector elements and the input values depends on the model implementation.
   * @param input model input to set
   */
  virtual void setInput(const std::vector<double>& input) = 0;
  /**
   * @brief Use the provided @p input to update the @ref input_ .
   *
   * Only the non-NaN values in the @p input will overwrite the corresponding values in the @ref input_ .
   * The internal mapping between the vector elements and the input values depends on the model implementation.
   * @param input model input used to update the current one
   */
  virtual void updateInput(const std::vector<double>& input) = 0;

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

  bool existing() const { return existing_; }
  bool active() const { return active_; }
  const prescan::sim::StateActuatorUnit& state() const;

 protected:
  /**
   * @brief Use the @ref state_input_ to update the @ref state_ .
   *
   * Any `NaN` values in the @ref state_input_ are ignored
   * and the corresponding values in the @ref state_ are not changed.
   */
  virtual void updateState() = 0;

  bool existing_;                            ///< Whether the model is already present in the experiment
  bool active_;                              ///< Whether the model will step in the simulation
  prescan::sim::StateActuatorUnit* state_;   ///< The state of the entity in the simulation
  prescan::api::types::WorldObject object_;  ///< The object in the simulation this model is attached to
};

}  // namespace symaware
