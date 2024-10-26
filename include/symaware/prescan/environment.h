/**
 * @file environment.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Environment class.
 */
#pragma once

#include <cstdint>
#include <prescan/api/Viewer.hpp>
#include <prescan/api/experiment.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "symaware/prescan/data.h"
#include "symaware/prescan/type.h"

namespace symaware {

// Forward declaration
class Entity;
class Road;
class EntityModel;

class Environment {
 public:
  Environment();
  explicit Environment(const std::string& file_path);

  /**
   * @brief Set the environment weather to the specified type and fog visibility
   *
   * A negative value for fog_visibility will disable the fog all together
   * @param weather_type type of weather
   * @param fog_visibility visibility of the fog
   * @return reference to the environment
   */
  Environment& setWeather(WeatherType weather_type = WeatherType::SUNNY, double fog_visibility = -1);
  /**
   * @brief Set the environment sky to the specified type and light pollution
   * @param sky_type moment of the day
   * @param light_pollution level of light pollution. Can be disabled with SkyLightPollutionNone
   * @return reference to the environment
   */
  Environment& setSky(SkyType sky_type = SkyType::DAY,
                      prescan::api::types::SkyLightPollution light_pollution =
                          prescan::api::types::SkyLightPollution::SkyLightPollutionNone);
  /**
   * @brief Set the scheduler frequencies
   *
   * Only used if the simulation step is not handled manually by the user
   * @param simulation_frequency the frequency at which the simulation will run
   * @param integration_frequency the frequency at which the integration will run
   * @return reference to the environment
   */
  Environment& setSchedulerFrequencies(std::int32_t simulation_frequency, std::int32_t integration_frequency);
  /**
   * @brief Set the scheduler speed
   *
   * Only used if the simulation step is not handled manually by the user
   * @param simulation_speed speed of the simulation
   * @param ignore_frame_overrun whether to ignore frame overrun
   * @return reference to the environment
   */
  Environment& setSchedulerSpeed(prescan::api::types::SimulationSpeed simulation_speed, bool ignore_frame_overrun);

  /**
   * @brief Create a free camera viewer for the environment.
   *
   * The viewer will allow for the visualisation of the environment using the Prescan viewer using a free camera.
   * @return the new viewer
   */
  prescan::api::viewer::Viewer addFreeViewer();
  /**
   * @brief Remove all viewers from the environment.
   * @warning All previously created viewers will be invalidated
   */
  void removeAllViewers();

  /**
   * @brief Add a model to the environment.
   *
   * It can add a model to the environment without linking it to any entity.
   * Useful to gather information about a model you may not want to run in the simulation.
   * @param model model to add
   * @return Environment& instance reference
   */
  Environment& addModel(EntityModel& model);
  /**
   * @brief Remove a model from the environment.
   *
   * Removes a model added with @ref addModel from the environment.
   * @param model model to remove
   * @return Environment& instance reference
   */
  Environment& removeModel(EntityModel& model);

  /**
   * @brief Add an entity to the environment.
   *
   * The entity will be placed in the world at the specified position and orientation.
   * If the operation is successful, the @p entity will be initialised with the object created in the simulation.
   * @note Cannot register entities of type @ref ObjectType::Existing ,
   * since this type is used to represent pre-existing objects in the simulation.
   * Use @ref addEntity(const std::string&, Entity&) instead
   * @param[in,out] entity entity representing the new object to be added
   * @return instance reference
   */
  Environment& addEntity(Entity& entity);

  /**
   * @brief Collect an existing @p entity from the experiment by it by its @p name.
   *
   * The entity with the specified name must exist in the experiment.
   * @note If the type of the entity is @ref ObjectType::Existing, the setup will be ignored
   * and the model will not be initialised.
   * If the former step is needed, use the @ref applySetup method.
   * @param name name of the entity in the environment
   * @param[out] entity collected entity
   * @return instance reference
   */
  Environment& addEntity(const std::string& name, Entity& entity);

  /**
   * @brief Remove an @p entity from both the experiment and the environment.
   *
   * If the @p entity is not present in the @ref entities_ map, the operation will be ignored.
   * @param entity entity to remove
   * @return instance reference
   */
  Environment& removeEntity(Entity& entity);
  /**
   * @brief Remove an entity with this @p name from the environment.
   *
   * Even if the entity is not present in the @ref entities_ map,
   * the entity will be removed from the experiment.
   * @param name name of the entity to remove
   * @return instance reference
   */
  Environment& removeEntity(const std::string& name);

  /**
   * @brief Add a road to the environment.
   *
   * The road will be placed in the world at the specified @p position .
   * The road the be customised further by altering the returned object.
   * @note By default the road will not have any lanes.
   * Add them using the @ref Road::addLane method.
   * @param position position of the road in the world
   * @return the new road
   */
  Road addRoad(const Position& position = Position{true});

  /**
   * @brief Imports an OpenDRIVE network in the experiment.
   *
   * There are the following requirements for importing an OpenDRIVE file:
   * - the file should exist exist
   * - the file should adhere to the OpenDRIVE V1.4 specification, Revision H
   * - the experiment should not contain any roads yet
   * @param filename path to the OpenDRIVE file
   * @throw std::runtime_error if any of the conditions are not met
   * @return instance reference
   */
  Environment& importOpenDriveNetwork(const std::string& filename);

  /**
   * @brief Get the experiment object of the environment
   * @return experiment object
   */
  const prescan::api::experiment::Experiment& experiment() const { return experiment_; }

  /**
   * @brief Get the names of the entities in the environment
   * @return names of the entities
   */
  const std::unordered_map<std::string, Entity*>& entities() const { return entities_; }

  /**
   * @brief Get the models in the environment
   * @return models
   */
  const std::vector<EntityModel*>& models() const { return models_; }

  /**
   * @brief Save the internal file to a file
   * @param filename name of the file
   */
  void saveExperiment(const std::string& filename) { experiment_.saveToFile(filename); }

  /**
   * @brief Get an object from the environment by name
   * @tparam T type of object
   * @param object_name name of the object
   * @return object
   * @throw std::runtime_error if the object does not exist
   */
  template <class T>
  T getObject(const std::string& object_name) {
    return experiment_.getObjectByName<T>(object_name);
  }

 private:
  prescan::api::experiment::Experiment experiment_;
  std::unordered_map<std::string, Entity*> entities_;
  std::vector<EntityModel*> models_;
};

}  // namespace symaware
