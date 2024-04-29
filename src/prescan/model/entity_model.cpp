#include "symaware/prescan/model/entity_model.h"

#include <fmt/core.h>

#include <cmath>
#include <prescan/api/Vehicledynamics.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/api/vehicledynamics/AmesimPreconfiguredDynamics.hpp>

#include "symaware/util/exception.h"

namespace symaware {

EntityModel::EntityModel() : object_{}, state_{nullptr} {}

void EntityModel::initialiseObject(prescan::api::experiment::Experiment& experiment,
                                   prescan::api::types::WorldObject object) {
  object_ = object;
}

void EntityModel::registerUnit(const prescan::api::experiment::Experiment& experiment,
                               prescan::sim::ISimulation* simulation) {
  if (state_ != nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has alreasy been registered to a state");
  state_ = prescan::sim::registerUnit<prescan::sim::StateActuatorUnit>(simulation, object_);
}

void EntityModel::initialise(prescan::sim::ISimulation* simulation) {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has not been registered to a state");
  updateState();
}

void EntityModel::step(prescan::sim::ISimulation* simulation) {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has not been registered to a state");
  updateState();
}

void EntityModel::terminate(prescan::sim::ISimulation* simulation) {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has not been registered to a state");
  state_ = nullptr;
}

const prescan::sim::StateActuatorUnit& EntityModel::state() const {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("EntityModel has not been registered to a state");
  return *state_;
}

}  // namespace symaware