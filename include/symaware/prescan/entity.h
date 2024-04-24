/**
 * @file entity.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Entity class
 */
#pragma once

#include <prescan/api/types/WorldObject.hpp>
#include <string>

#include "symaware/prescan/dynamical_model.h"
#include "symaware/prescan/environment.h"

namespace symaware {
class Entity {
 public:
  Entity(Environment::ObjectType type);
  Entity(Environment::ObjectType type, DynamicalModel& model);
  Entity(Environment::ObjectType type, DynamicalModel* model);

  void initialise(prescan::api::types::WorldObject object);

  void step();

  Environment::ObjectType type() const { return type_; }
  const DynamicalModel& model() const { return *model_; }
  const prescan::api::types::WorldObject& object() const { return object_; }
  bool is_initialized() const { return is_initialized_; }

 protected:
  Environment::ObjectType type_;  ///< The type of the entity
  DynamicalModel* model_;         ///< The dynamical model of the entity. Only present if the entity is controllable
  prescan::api::types::WorldObject object_;  ///< The object that represents the entity in the simulation
  bool is_initialized_{false};               ///< Whether the entity has been initialized
};

}  // namespace symaware
