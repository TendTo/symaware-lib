#include "symaware/prescan/dynamical_model.h"

#include <prescan/api/types/WorldObject.hpp>

#include "symaware/prescan/entity.h"
#include "symaware/util/exception.h"

namespace symaware {

DynamicalModel::DynamicalModel() : entity_{nullptr}, state_{nullptr} {}

void DynamicalModel::initialise_entity(const Entity& entity) {
  if (entity_ != nullptr) SYMAWARE_RUNTIME_ERROR("DynamicalModel is already linked to an entity");
  entity_ = &entity;
}

void DynamicalModel::registerUnit(prescan::api::experiment::Experiment& experiment,
                                  prescan::sim::ISimulation* simulation) {
  if (entity_ == nullptr) SYMAWARE_RUNTIME_ERROR("DynamicalModel has not been linked to an entity yet");
  if (state_ != nullptr) SYMAWARE_RUNTIME_ERROR("DynamicalModel has alreasy been registered to a state");
  state_ = prescan::sim::registerUnit<prescan::sim::StateActuatorUnit>(simulation, entity_->object());
}

void DynamicalModel::initialise(prescan::sim::ISimulation* simulation) {}

void DynamicalModel::step(prescan::sim::ISimulation* simulation) {}

void DynamicalModel::terminate(prescan::sim::ISimulation* simulation) {}

}  // namespace symaware