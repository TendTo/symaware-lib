#include "symaware/prescan/model/entity_model.h"

#include <fmt/core.h>

#include <cmath>
#include <prescan/api/Vehicledynamics.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/api/vehicledynamics/AmesimPreconfiguredDynamics.hpp>

#include "symaware/prescan/entity.h"
#include "symaware/util/exception.h"

#define ENSURE_OBJECT_NOT_NULL(object, message)                        \
  do {                                                                 \
    try {                                                              \
      if (object.handle() == nullptr) SYMAWARE_RUNTIME_ERROR(message); \
    } catch (const std::exception& e) {                                \
      SYMAWARE_RUNTIME_ERROR(message);                                 \
    }                                                                  \
  } while (0)

namespace symaware {

EntityModel::EntityModel(const bool existing, const bool active)
    : existing_{existing}, active_{active}, state_{nullptr} {}

void EntityModel::linkEntity(const prescan::api::types::WorldObject& object) {
  ENSURE_OBJECT_NOT_NULL(object, "Object is null");
  object_ = object;
}
void EntityModel::linkEntity(const Entity& entity) {
  ENSURE_OBJECT_NOT_NULL(entity.object(), "Entity object has not been initialised yet");
  object_ = entity.object();
}

void EntityModel::registerUnit(const prescan::api::experiment::Experiment& experiment,
                               prescan::sim::ISimulation* simulation) {
  ENSURE_OBJECT_NOT_NULL(object_, "EntityModel has not been linked to an object");
  if (!active_) return;
  if (state_ != nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has alreasy been registered to a state");
  state_ = prescan::sim::registerUnit<prescan::sim::StateActuatorUnit>(simulation, object_);
}

void EntityModel::createIfNotExists(prescan::api::experiment::Experiment& experiment) {
  if (existing_) return;
  ENSURE_OBJECT_NOT_NULL(object_, "EntityModel has not been linked to an object");
}

void EntityModel::initialise(prescan::sim::ISimulation* simulation) {
  if (!active_) return;
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has not been registered to a state");
  state_->stateActuatorInput();
  updateState();
}

void EntityModel::step(prescan::sim::ISimulation* simulation) {
  if (!active_) return;
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has not been registered to a state");
  updateState();
}

void EntityModel::terminate(prescan::sim::ISimulation* simulation) {
  if (!active_) return;
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has not been registered to a state");
  state_ = nullptr;
}

const prescan::sim::StateActuatorUnit& EntityModel::state() const {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has not been registered to a state");
  return *state_;
}

}  // namespace symaware