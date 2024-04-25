#include "symaware/prescan/entity.h"

#include "symaware/util/exception.h"

namespace symaware {

Entity::Entity(Environment::ObjectType type) : type_{type}, model_{nullptr}, object_{}, is_initialized_{false} {}

Entity::Entity(Environment::ObjectType type, DynamicalModel& model)
    : type_{type}, model_{&model}, object_{}, is_initialized_{false} {
  model_->initialiseObject(object_);
}

Entity::Entity(Environment::ObjectType type, DynamicalModel* model)
    : type_{type}, model_{model}, object_{}, is_initialized_{false} {
  if (model_ != nullptr) model_->initialiseObject(object_);
}

void Entity::initialise(prescan::api::types::WorldObject object) {
  if (is_initialized_) SYMAWARE_RUNTIME_ERROR("Entity has already been initialized");
  object_ = object;
  is_initialized_ = true;
  object_.setMovable(model_ != nullptr);
}

void Entity::step() {}

}  // namespace symaware
