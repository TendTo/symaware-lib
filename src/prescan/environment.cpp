#include "symaware/prescan/environment.h"

#include <iostream>

#include "symaware/util/exception.h"

namespace symaware {

Environment::Environment() : experiment_{prescan::api::experiment::createExperiment()} {}

void Environment::setWeather(const WeatherType weather_type, const double fog_visibility) {
  prescan::api::types::Weather weather = experiment_.weather();
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
      break;
  }
  if (fog_visibility < 0) {
    weather.fog().setEnabled(false);
  } else {
    weather.fog().setEnabled(true);
    weather.fog().setVisibility(fog_visibility);
  }
}

}  // namespace symaware