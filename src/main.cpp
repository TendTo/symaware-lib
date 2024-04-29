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

#define M_PI 3.14159265358979323846

#if 1

int main()
{
  symaware::Environment env;
  auto viewer = env.createFreeViewer();
  env.setSky(symaware::Environment::SkyType::DAY);
  env.setWeather(symaware::Environment::WeatherType::SUNNY);

  symaware::DynamicalModel toyota_model{};
  symaware::DynamicalModel audi_a8_model{};

  symaware::Entity toyota{
      symaware::Environment::ObjectType::Toyota_Yaris_Hatchback,
      symaware::EntitySetup{true, true, true, prescan::api::types::SensorDetectability::SensorDetectabilityDetectable},
      toyota_model};
  symaware::Entity audi_a8{
      symaware::Environment::ObjectType::Audi_A8_Sedan,
      symaware::EntitySetup{{0, 3, 0},
                            {0, 0, 0},
                            {0, 0, 0},
                            true,
                            true,
                            prescan::api::types::SensorDetectability::SensorDetectabilityDetectable},
      audi_a8_model};
  env.addEntity(toyota);
  env.addEntity(audi_a8);

  symaware::Simulation simulation(env);
  simulation.setLogLever(prescan::sim::ISimulationLogger::LogLevel::LogLevelInfo);
#if 0
  simulation.run(1000);
#else
  const int max_steps = 150;
  for (int i = 0; i < max_steps; i++)
  {
    symaware::DynamicalModelInput input{false};
    if (i <= 100)
      input = {1, 0, 2.0 * M_PI * i / max_steps - M_PI, symaware::Gear::Forward};
    else
      input = {0, 1, 2.0 * M_PI * i / max_steps - M_PI, symaware::Gear::Neutral};
    toyota_model.setInput(input);
    audi_a8_model.setInput(input);
    simulation.step();
    std::this_thread::sleep_for(100ms);
  }

  simulation.terminate();
#endif

  return 0;
}

#else

int main()
{
  symaware::Environment env{
      "C:/Users/Public/Documents/Experiments/DemoExperiments/Demo_3D_Dynamics/Demo_3D_Dynamics.pb"};

  symaware::Simulation simulation(env);
#if 0
  simulation.run(1000);
#else
  for (int i = 0; i < 100; i++)
  {
    simulation.step();
    std::this_thread::sleep_for(100ms);
  }

  simulation.terminate();
#endif
  return 0;
}

#endif