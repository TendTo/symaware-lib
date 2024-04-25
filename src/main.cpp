/**
 * @file main.cpp
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Main
 */
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <chrono>
#include <filesystem>
#include <iostream>
#include <prescan/api/Air.hpp>
#include <prescan/api/Experiment.hpp>
#include <prescan/api/Viewer.hpp>
#include <prescan/sim/ISimulationLogger.hpp>
#include <prescan/sim/ManualSimulation.hpp>
#include <prescan/sim/Simulation.hpp>
#include <thread>

#include "symaware/symaware.h"

using namespace std::chrono_literals;

int main() {
  symaware::Environment env;
  env.createFreeViewer();
  env.setSky(symaware::Environment::SkyType::DAY);
  env.setWeather(symaware::Environment::WeatherType::SNOWY);

  symaware::DynamicalModel audi_a3_model;
  symaware::DynamicalModel audi_a8_model;

  symaware::Entity audi_a3{
      symaware::Environment::ObjectType::Audi_A3,
      symaware::EntityState{true, true, true, prescan::api::types::SensorDetectability::SensorDetectabilityDetectable},
      audi_a3_model};
  symaware::Entity audi_a8{
      symaware::Environment::ObjectType::Audi_A8_Sedan,
      symaware::EntityState{{10, 10, 10},
                            {0, 0, 0},
                            {0, 0, 0},
                            true,
                            true,
                            prescan::api::types::SensorDetectability::SensorDetectabilityDetectable},
      audi_a8_model};
  env.addEntity(audi_a3);
  env.addEntity(audi_a8);

  symaware::Simulation simulation(env);
  simulation.setLogLever(prescan::sim::ISimulationLogger::LogLevel::LogLevelInfo);

  for (int i = 0; i < 100; i++) {
    simulation.step();
    std::this_thread::sleep_for(100ms);
  }

  simulation.terminate();

  return 0;
}