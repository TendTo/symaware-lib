#include "symaware/prescan/environment.h"

#include <iostream>
#include <prescan/api/Opendrive.hpp>

#include "symaware/prescan/entity.h"
#include "symaware/prescan/model/entity_model.h"
#include "symaware/prescan/road.h"
#include "symaware/util/exception.h"

namespace symaware {

Environment::Environment() : experiment_{prescan::api::experiment::createExperiment()} {}
Environment::Environment(const std::string& filename)
    : experiment_{prescan::api::experiment::loadExperimentFromFile(filename)} {}

Environment& Environment::setWeather(const WeatherType weather_type, const double fog_visibility) {
  prescan::api::types::Weather weather{experiment_.weather()};
  switch (weather_type) {
    case WeatherType::SUNNY:
      weather.precipitation().setDisabled();
      break;
    case WeatherType::RAINY:
      weather.precipitation().setDefaultRain();
      break;
    case WeatherType::SNOWY:
      weather.precipitation().setDefaultSnow();
      break;
    default:
      SYMAWARE_UNREACHABLE();
  }
  if (fog_visibility < 0) {
    weather.fog().setEnabled(false);
  } else {
    weather.fog().setEnabled(true);
    weather.fog().setVisibility(fog_visibility);
  }
  return *this;
}

Environment& Environment::setSky(const SkyType sky_type, const prescan::api::types::SkyLightPollution light_pollution) {
  prescan::api::types::Sky sky{experiment_.sky()};
  switch (sky_type) {
    case SkyType::DAWN:
      sky.setPresetDawn();
      break;
    case SkyType::DAY:
      sky.setPresetDay();
      break;
    case SkyType::DUSK:
      sky.setPresetDusk();
      break;
    case SkyType::NIGHT:
      sky.setPresetNight();
      break;
    default:
      SYMAWARE_UNREACHABLE();
  }
  sky.setLightPollution(light_pollution);
  return *this;
}

Environment& Environment::setSchedulerFrequencies(std::int32_t simulation_frequency,
                                                  std::int32_t integration_frequency) {
  experiment_.scheduler().setFrequencies(simulation_frequency, integration_frequency);
  return *this;
}

Environment& Environment::setSchedulerSpeed(const prescan::api::types::SimulationSpeed simulation_speed,
                                            const bool ignore_frame_overrun) {
  experiment_.scheduler().setSimulationSpeed(simulation_speed);
  experiment_.scheduler().setIgnoreFrameOverrun(ignore_frame_overrun);
  return *this;
}

Environment& Environment::addEntity(Entity& entity) {
  if (entity.is_initialised()) return *this;

  if (entity.type() == ObjectType::Existing)
    SYMAWARE_RUNTIME_ERROR("Existing entities cannot be created. Use the addEntity(std::string, Entity) method");
  entity.initialiseObject(experiment_, experiment_.createObject(to_string(entity.type())));
  entities_[entity.name()] = &entity;
  return *this;
}

Environment& Environment::addEntity(const std::string& name, Entity& entity) {
  if (entity.is_initialised()) return *this;

  entity.initialiseObject(experiment_, experiment_.getObjectByName<prescan::api::types::WorldObject>(name));
  entities_[entity.name()] = &entity;
  return *this;
}

Environment& Environment::removeEntity(Entity& entity) {
  if (!entity.is_initialised()) return *this;         // The entity was never initialised
  if (!entities_.erase(entity.name())) return *this;  // The entity was not found in the environment
  entity.remove();
  return *this;
}
Environment& Environment::removeEntity(const std::string& name) {
  entities_.erase(name);
  experiment_.getObjectByName<prescan::api::types::WorldObject>(name).remove();
  return *this;
}

Road Environment::addRoad(const Position& position) { return Road{*this}.setPosition(position); }

Environment& Environment::importOpenDriveNetwork(const std::string& filename) {
  prescan::api::opendrive::importOpenDriveFile(experiment_, filename);
  return *this;
}

prescan::api::viewer::Viewer Environment::addFreeViewer() {
  prescan::api::viewer::Viewer viewer{prescan::api::viewer::createViewer(experiment_)};
  viewer.assignFreeCamera();
  return viewer;
}
void Environment::removeAllViewers() {
  for (prescan::api::viewer::Viewer& viewer : prescan::api::viewer::getViewers(experiment_).asVector()) viewer.remove();
}

}  // namespace symaware