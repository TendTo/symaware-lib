/**
 * @file main.cpp
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Main example
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

#define M_PI 3.14159265358979323846

int main() {
  symaware::Environment env;
  auto viewer = env.addFreeViewer();
  env.setSky(symaware::SkyType::DAY);
  env.setWeather(symaware::WeatherType::SUNNY);
  env.addRoad().addStraightSection(100).addLane(prescan::api::roads::types::RoadSideType::RoadSideTypeLeft, 3.5);

  symaware::AmesimDynamicalModel toyota_model{};
  symaware::TrackModel audi_a8_model{{false,
                                      true,
                                      {{0, 0, 0},
                                       {1, 1, 0},
                                       {2, 2, 0},
                                       {3, 3, 0},
                                       {4, 4, 0},
                                       {5, 5, 0},
                                       {4, 6, 0},
                                       {3, 7, 0},
                                       {2, 8, 0},
                                       {1, 9, 0},
                                       {0, 10, 0}},
                                      5,
                                      0.1}};
  symaware::CustomDynamicalModel baloon_model{};

  symaware::Entity baloon{
      symaware::ObjectType::BalloonCar,
      symaware::Entity::Setup{{4, 5, 0},
                              {0, 0, 0},
                              {0, 0, 0},
                              true,
                              true,
                              prescan::api::types::SensorDetectability::SensorDetectabilityDetectable},
      baloon_model};
  symaware::Entity toyota{
      symaware::ObjectType::Toyota_Yaris_Hatchback,
      symaware::Entity::Setup{true, true, true,
                              prescan::api::types::SensorDetectability::SensorDetectabilityDetectable},
      toyota_model};
  symaware::Entity audi_a8{
      symaware::ObjectType::Audi_A8_Sedan,
      symaware::Entity::Setup{{0, 3, 0},
                              {0, 0, 0},
                              {0, 0, 0},
                              true,
                              true,
                              prescan::api::types::SensorDetectability::SensorDetectabilityDetectable},
      audi_a8_model};

  env.addEntity(baloon);
  env.addEntity(toyota);
  env.addEntity(audi_a8);

  symaware::Simulation simulation(env);
  simulation.setLogLevel(prescan::sim::ISimulationLogger::LogLevel::LogLevelInfo);
  simulation.initialise();

  const int max_steps = 150;
  for (int i = 0; i < max_steps; i++) {
    std::vector<double> input;
    if (i <= 100)
      input = {1, 0, 2.0 * M_PI * i / max_steps - M_PI, symaware::Gear::Forward};
    else
      input = {0, 1, 2.0 * M_PI * i / max_steps - M_PI, symaware::Gear::Neutral};
    toyota_model.setInput(input);
    audi_a8_model.setInput(input);
    baloon_model.setInput({
        {i, i, i},
        {i, i, i},
        {i, i, i},
        {i, i, i},
        {i, i, i},
    });
    simulation.step();
    std::this_thread::sleep_for(100ms);
  }

  simulation.terminate();

  return 0;
}
