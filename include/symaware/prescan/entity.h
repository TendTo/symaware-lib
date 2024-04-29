/**
 * @file entity.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Entity class
 */
#pragma once

#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/SelfSensorUnit.hpp>
#include <string>

#include "symaware/prescan/data.h"
#include "symaware/prescan/model/dynamical_model.h"
#include "symaware/prescan/environment.h"

namespace symaware {
class Entity {
 public:
  Entity(Environment::ObjectType type, DynamicalModel& model);
  Entity(Environment::ObjectType type, EntitySetup setup, DynamicalModel& model);
  Entity(Environment::ObjectType type, EntitySetup setup = {}, DynamicalModel* model = nullptr);

  void initialiseObject(prescan::api::experiment::Experiment& experiment, prescan::api::types::WorldObject object);

  /**
   * @brief Forwards the registration of the model to the model itself, if present.
   *
   * Called at the beginning of the @p simulation.
   * @param experiment experiment about to be run
   * @param simulation simulation that will run the experiment
   */
  void registerUnit(const prescan::api::experiment::Experiment& experiment, prescan::sim::ISimulation* simulation);
  /**
   * @brief Forwards the initialisation of the model to the model itself, if present.
   *
   * Called before the first step of the @p simulation.
   * @param simulation simulation that is about to run the experiment
   */
  void initialise(prescan::sim::ISimulation* simulation);
  /**
   * @brief Forwards the step of the model to the model itself, if present.
   *
   * Called at each step of the @p simulation.
   * @param simulation simulation that is running the experiment
   */
  void step(prescan::sim::ISimulation* simulation);
  /**
   * @brief Forwards the termination of the model to the model itself, if present.
   *
   * Called at the end of the @p simulation.
   * @param simulation simulation that has run the experiment
   */
  void terminate(prescan::sim::ISimulation* simulation);

  EntityState state() const;
  Environment::ObjectType type() const { return type_; }
  const EntitySetup& setup() const { return setup_; }
  const DynamicalModel* model() const { return model_; }
  const prescan::api::types::WorldObject& object() const { return object_; }
  bool is_initialized() const { return is_initialized_; }

 private:
  void updateObject();

  bool is_initialized_{false};    ///< Whether the entity has been initialized
  Environment::ObjectType type_;  ///< The type of the entity
  EntitySetup setup_;             ///< The initial state of the entity
  DynamicalModel* model_;         ///< The dynamical model of the entity. Only present if the entity is controllable
  prescan::api::types::WorldObject object_;    ///< The object that represents the entity in the simulation
  const prescan::sim::SelfSensorUnit* state_;  ///< The state of the entity in the simulation
};

}  // namespace symaware
