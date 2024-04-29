#include "symaware/prescan/entity.h"

#include <cmath>
#include <ostream>

#include "symaware/util/exception.h"

namespace symaware {

Entity::Entity(const Environment::ObjectType type, EntityModel& model) : Entity{type, Setup{}, &model} {}
Entity::Entity(const Environment::ObjectType type, Setup setup, EntityModel& model)
    : Entity{type, std::move(setup), &model} {}
Entity::Entity(const Environment::ObjectType type, Setup setup, EntityModel* const model)
    : is_initialized_{false}, type_{type}, setup_{std::move(setup)}, model_{model}, object_{}, state_{nullptr} {}

Entity::Entity(const std::string& name, Environment& environment, EntityModel& model)
    : Entity{name, environment, &model} {}
Entity::Entity(const std::string& name, Environment& environment, EntityModel* const model)
    : is_initialized_{false},
      type_{Environment::ObjectType::Object},  // TODO: can this be inferred from the experiment?
      setup_{},
      model_{model},
      object_{environment.experiment().getObjectByName<prescan::api::types::WorldObject>(name)},
      state_{nullptr} {
  environment.appendEntitiy(*this);
}

Entity::Entity(const std::string& name, Environment& environment, Setup setup, EntityModel& model)
    : Entity{name, environment, std::move(setup), &model} {}
Entity::Entity(const std::string& name, Environment& environment, Setup setup, EntityModel* const model)
    : is_initialized_{false},
      type_{Environment::ObjectType::Object},  // TODO: can this be inferred from the experiment?
      setup_{std::move(setup)},
      model_{model},
      object_{environment.experiment().getObjectByName<prescan::api::types::WorldObject>(name)},
      state_{nullptr} {
  updateObject();
  environment.appendEntitiy(*this);
}

void Entity::initialiseObject(prescan::api::experiment::Experiment& experiment,
                              const prescan::api::types::WorldObject object) {
  if (is_initialized_) SYMAWARE_RUNTIME_ERROR("Entity has already been initialized");
  is_initialized_ = true;

  object_ = object;
  updateObject();
  model_->initialiseObject(experiment, object_);
}

Entity::State Entity::state() const {
  if (state_ == nullptr) SYMAWARE_RUNTIME_ERROR("Entity has not been registered to a state in the simulation");
  return State{Position{state_->selfSensorOutput().PositionX, state_->selfSensorOutput().PositionY,
                        state_->selfSensorOutput().PositionZ},
               Orientation{state_->selfSensorOutput().OrientationRoll, state_->selfSensorOutput().OrientationPitch,
                           state_->selfSensorOutput().OrientationYaw},
               state_->selfSensorOutput().Velocity, state_->selfSensorOutput().Yaw_rate};
}

void Entity::updateObject() {
  object_.setMovable(setup_.is_movable);
  object_.setSensorDetectability(setup_.sensor_detectability);
  object_.setCollisionDetectable(setup_.is_collision_detectable);
  if (!std::isnan(setup_.cog_offset.x)) object_.cogOffset().setX(setup_.cog_offset.x);
  if (!std::isnan(setup_.cog_offset.y)) object_.cogOffset().setY(setup_.cog_offset.y);
  if (!std::isnan(setup_.cog_offset.z)) object_.cogOffset().setZ(setup_.cog_offset.z);
  if (!std::isnan(setup_.orientation.roll)) object_.pose().orientation().setRoll(setup_.orientation.roll);
  if (!std::isnan(setup_.orientation.pitch)) object_.pose().orientation().setPitch(setup_.orientation.pitch);
  if (!std::isnan(setup_.orientation.yaw)) object_.pose().orientation().setYaw(setup_.orientation.yaw);
  if (!std::isnan(setup_.position.x)) object_.pose().position().setX(setup_.position.x);
  if (!std::isnan(setup_.position.y)) object_.pose().position().setY(setup_.position.y);
  if (!std::isnan(setup_.position.z)) object_.pose().position().setZ(setup_.position.z);
}

void Entity::registerUnit(const prescan::api::experiment::Experiment& experiment,
                          prescan::sim::ISimulation* const simulation) {
  state_ = prescan::sim::registerUnit<prescan::sim::SelfSensorUnit>(simulation, object_);
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

std::ostream& operator<<(std::ostream& os, const Entity::Setup& setup) {
  return os << "Entity::Setup: (position: " << setup.position << ", orientation: " << setup.orientation
            << ", cog_offset: " << setup.cog_offset << ", is_movable: " << setup.is_movable
            << ", sensor_detectability: " << setup.sensor_detectability
            << ", is_collision_detectable: " << setup.is_collision_detectable << ")";
}
std::ostream& operator<<(std::ostream& os, const Entity::State& state) {
  return os << "Entity::State: (position: " << state.position << ", orientation: " << state.orientation
            << ", velocity: " << state.velocity << ", yaw_rate: " << state.yaw_rate << ")";
}

}  // namespace symaware
