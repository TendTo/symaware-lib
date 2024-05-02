#include "symaware/prescan/entity.h"

#include <cmath>
#include <ostream>

#include "symaware/util/exception.h"

namespace symaware {

Entity::Setup::Setup(Position position, Orientation orientation, Position cog_offset, bool is_collision_detectable,
                     bool is_movable, prescan::api::types::SensorDetectability sensor_detectability)
    : position{position},
      orientation{orientation},
      cog_offset{cog_offset},
      is_collision_detectable{is_collision_detectable},
      is_movable{is_movable},
      sensor_detectability{sensor_detectability} {}

Entity::Setup::Setup(bool zero_init, bool is_collision_detectable, bool is_movable,
                     prescan::api::types::SensorDetectability sensor_detectability)
    : position{zero_init},
      orientation{zero_init},
      cog_offset{zero_init},
      is_collision_detectable{is_collision_detectable},
      is_movable{is_movable},
      sensor_detectability{sensor_detectability} {}

Entity::State::State(Position position, Orientation orientation, double velocity, double yaw_rate)
    : position{position}, orientation{orientation}, velocity{velocity}, yaw_rate{yaw_rate} {}

Entity::State::State(bool zero_init)
    : position{zero_init},
      orientation{zero_init},
      velocity{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()},
      yaw_rate{zero_init ? 0 : std::numeric_limits<double>::quiet_NaN()} {}

Entity::Entity(const Environment::ObjectType type, EntityModel& model) : Entity{type, Setup{}, &model} {}
Entity::Entity(const Environment::ObjectType type, Setup setup, EntityModel& model)
    : Entity{type, std::move(setup), &model} {}
Entity::Entity(const Environment::ObjectType type, Setup setup, EntityModel* const model)
    : type_{type}, setup_{std::move(setup)}, model_{model}, object_{}, state_{nullptr} {
  if (type_ == Environment::ObjectType::Existing) SYMAWARE_RUNTIME_ERROR("Existing type cannot be used directly");
}

Entity::Entity(const std::string& name, Environment& environment, EntityModel& model)
    : Entity{name, environment, &model} {}
Entity::Entity(const std::string& name, Environment& environment, EntityModel* const model)
    : type_{Environment::ObjectType::Existing},
      setup_{},
      model_{model},
      object_{environment.experiment().getObjectByName<prescan::api::types::WorldObject>(name)},
      state_{nullptr} {
  if (model_ != nullptr) model_->setObject(object_);
  environment.addEntity(*this);
}

void Entity::applySetup(Setup setup) {
  setup_ = std::move(setup);
  updateObject();
}

void Entity::initialiseObject(prescan::api::experiment::Experiment& experiment,
                              const prescan::api::types::WorldObject object) {
  object_ = object;
  updateObject();
  if (model_ != nullptr) model_->initialiseObject(experiment, object_);
}

Entity::State Entity::state() const {
  if (state_ == nullptr) return State{false};
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
  // TODO: a flag may be needed if registering the SelfSensorUnit is expensive over objects that will not be used
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
std::ostream& operator<<(std::ostream& os, const Entity& entity) {
  os << std::boolalpha;
  os << "Entity: (type: " << entity.type() << ", setup: " << entity.setup();
  if (entity.model() != nullptr) os << ", model: " << entity.model();
  os << ", state: " << entity.state() << ")";
  os << std::noboolalpha;
  return os;
}

}  // namespace symaware
