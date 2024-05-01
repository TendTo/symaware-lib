/**
 * @file entity.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Entity class
 */
#pragma once

#include <fmt/ostream.h>

#include <iosfwd>
#include <limits>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/SelfSensorUnit.hpp>
#include <string>

#include "symaware/prescan/data.h"
#include "symaware/prescan/environment.h"
#include "symaware/prescan/model/entity_model.h"

namespace symaware {
class Entity {
 public:
  /** Setup configuration for a generic entity */
  struct Setup {
    Setup() = default;
    Setup(Position position, Orientation orientation, Position cog_offset, bool is_collision_detectable,
          bool is_movable, prescan::api::types::SensorDetectability sensor_detectability);
    Setup(bool zero_init, bool is_collision_detectable, bool is_movable,
          prescan::api::types::SensorDetectability sensor_detectability);
    Position position;             ///< The initial position of the entity in the world
    Orientation orientation;       ///< The initial orientation of the entity in the world
    Position cog_offset;           ///< The offset of the center of gravity of the entity
    bool is_collision_detectable;  ///< Whether the entity is detectable by collision sensors
    bool is_movable;               ///< Whether the entity is movable
    prescan::api::types::SensorDetectability sensor_detectability;  ///< The detectability of the entity by sensors
  };

  /** State of a generic entity at a given time */
  struct State {
    State() = default;
    explicit State(bool zero_init);
    State(Position position, Orientation orientation, double velocity, double yaw_rate);
    Position position;        ///< The position of the entity in the world
    Orientation orientation;  ///< The orientation of the entity in the world
    double velocity;          ///< The velocity of the entity
    double yaw_rate;          ///< The yaw rate of the entity
  };

  /**
   * @brief Construct a new Entity object with the given @p type.
   *
   * If a @p model is provided, the entity will be controlled by it during the simulation.
   * If a @p setup is provided, it is used to initialise the entity.
   * @note If this constructor is used, the entity must be added to the environment manually.
   * @param type type of the entity
   * @param setup initial state of the entity
   * @param model model that controls the entity
   */
  Entity(Environment::ObjectType type, Setup setup = {}, EntityModel* model = nullptr);
  /** @overload */
  Entity(Environment::ObjectType type, EntityModel& model);
  /** @overload */
  Entity(Environment::ObjectType type, Setup setup, EntityModel& model);

  /**
   * @brief Construct a new Entity object based on an existing object in the @p environment with the given @p name.
   *
   * If a @p model is provided, the entity will be controlled by it during the simulation.
   * No initialisation is performed.
   * @param name name of the object in the environment
   * @param environment environment where the object is located
   * @param model model that controls the entity
   */
  Entity(const std::string& name, Environment& environment, EntityModel& model);
  /** @overload */
  Entity(const std::string& name, Environment& environment, EntityModel* model = nullptr);

  /**
   * @brief Construct a new Entity object based on an existing object in the @p environment with the given @p name.
   *
   * The object is initialised with the given @p setup.
   * If a @p model is provided, the entity will be controlled by it during the simulation.
   * @note Only the object is initialised when using this constructor, but the model is not.
   * @param name name of the object in the environment
   * @param environment environment where the object is located
   * @param model model that controls the entity
   */
  Entity(const std::string& name, Environment& environment, Setup setup, EntityModel& model);
  /** @overload */
  Entity(const std::string& name, Environment& environment, Setup setup, EntityModel* model = nullptr);

  /**
   * @brief Initialise the object once the entity has been added to the environment.
   * @param experiment underlying experiment
   * @param object object this entity will represent
   */
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

  State state() const;
  Environment::ObjectType type() const { return type_; }
  const Setup& setup() const { return setup_; }
  const EntityModel* model() const { return model_; }
  const prescan::api::types::WorldObject& object() const { return object_; }
  bool is_initialized() const { return is_initialized_; }

 private:
  void updateObject();

  bool is_initialized_{false};    ///< Whether the entity has been initialized
  Environment::ObjectType type_;  ///< The type of the entity
  Setup setup_;                   ///< The initial state of the entity
  EntityModel* model_;            ///< The dynamical model of the entity. Only present if the entity is controllable
  prescan::api::types::WorldObject object_;    ///< The object that represents the entity in the simulation
  const prescan::sim::SelfSensorUnit* state_;  ///< The state of the entity in the simulation
};

std::ostream& operator<<(std::ostream& os, const Entity::Setup& setup);
std::ostream& operator<<(std::ostream& os, const Entity::State& state);
std::ostream& operator<<(std::ostream& os, const Entity& entity);

}  // namespace symaware

template <>
struct fmt::formatter<symaware::Entity::State> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::Entity::Setup> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<symaware::Entity> : fmt::ostream_formatter {};
