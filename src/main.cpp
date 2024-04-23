/**
 * @file main.cpp
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Main
 */
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <filesystem>
#include <iostream>
#include <prescan/api/Air.hpp>
#include <prescan/api/Experiment.hpp>
#include <prescan/sim/ISimulationLogger.hpp>
#include <prescan/sim/ManualSimulation.hpp>
#include <prescan/sim/Simulation.hpp>

#include "symaware/symaware.h"

int main() {
  symaware::Environment env;
  env.setSky(symaware::Environment::SkyType::DAY);
  env.setWeather(symaware::Environment::WeatherType::SNOWY);
  env.addAgent(symaware::Environment::ObjectType::Audi_A3);

  symaware::SimulationModel model(env);
  symaware::Simulation simulation(env, model);
  simulation.setLogLever(prescan::sim::ISimulationLogger::LogLevel::LogLevelCrawl);
  simulation.run(20);

  return 0;
}