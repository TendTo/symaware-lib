#include "symaware/prescan/entity.h"

#include <cmath>

#include "symaware/util/exception.h"

namespace symaware {

Entity::Entity(const Environment::ObjectType type, DynamicalModel& model)
    : is_initialized_{false}, type_{type}, state_{}, model_{&model}, object_{} {}

Entity::Entity(const Environment::ObjectType type, EntityState state, DynamicalModel& model)
    : is_initialized_{false}, type_{type}, state_{std::move(state)}, model_{&model}, object_{} {}

Entity::Entity(const Environment::ObjectType type, EntityState state, DynamicalModel* const model)
    : is_initialized_{false}, type_{type}, state_{std::move(state)}, model_{model}, object_{} {}

void Entity::initialiseObject(const prescan::api::types::WorldObject object) {
  if (is_initialized_) SYMAWARE_RUNTIME_ERROR("Entity has already been initialized");
  is_initialized_ = true;

  object_ = object;
  updateObject();

  if (model_ != nullptr) model_->initialiseObject(object_);
}

void Entity::updateObject() {
  object_.setMovable(state_.is_movable);
  object_.setSensorDetectability(state_.sensor_detectability);
  object_.setCollisionDetectable(state_.is_collision_detectable);
  if (!std::isnan(state_.cog_offset.x)) object_.cogOffset().setX(state_.cog_offset.x);
  if (!std::isnan(state_.cog_offset.y)) object_.cogOffset().setY(state_.cog_offset.y);
  if (!std::isnan(state_.cog_offset.z)) object_.cogOffset().setZ(state_.cog_offset.z);
  if (!std::isnan(state_.orientation.roll)) object_.pose().orientation().setRoll(state_.orientation.roll);
  if (!std::isnan(state_.orientation.pitch)) object_.pose().orientation().setPitch(state_.orientation.pitch);
  if (!std::isnan(state_.orientation.yaw)) object_.pose().orientation().setYaw(state_.orientation.yaw);
  if (!std::isnan(state_.position.x)) object_.pose().position().setX(state_.position.x);
  if (!std::isnan(state_.position.y)) object_.pose().position().setY(state_.position.y);
  if (!std::isnan(state_.position.z)) object_.pose().position().setZ(state_.position.z);
}

void Entity::registerUnit(const prescan::api::experiment::Experiment& experiment,
                          prescan::sim::ISimulation* const simulation) {
  if (model_ != nullptr) model_->registerUnit(experiment, simulation);
}
void Entity::initialise(prescan::sim::ISimulation* const simulation) {
  if (model_ != nullptr) model_->initialise(simulation);
}
void Entity::step(prescan::sim::ISimulation* const simulation) {
  if (model_ != nullptr) model_->step(simulation);
}
void Entity::terminate(prescan::sim::ISimulation* const simulation) {
  if (model_ != nullptr) model_->terminate(simulation);
}

}  // namespace symaware
