#pragma once

#include <prescan/api/experiment.hpp>

namespace symaware {
class Environment {
 public:
  enum class WeatherType { SUNNY, RAINY, SNOWY };
  Environment();

  void setRoad();
  /**
   * @brief Set the environment weather to the specified type and fog visibility
   *
   * A negative value for fog_visibility will disable the fog all together
   * @param weather_type type of weather
   * @param fog_visibility visibility of the fog
   */
  void setWeather(WeatherType weather_type = WeatherType::SUNNY, double fog_visibility = -1);

  void addBox();

 private:
  prescan::api::experiment::Experiment experiment_;
};

}  // namespace symaware
