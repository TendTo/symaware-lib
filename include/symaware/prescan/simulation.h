/**
 * @file simulation.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Simulation class
 */
#pragma once

#include <prescan/api/experiment/Experiment.hpp>
#include <prescan/sim/ISimulationModel.hpp>
#include <prescan/sim/ManualSimulation.hpp>

#include "symaware/prescan/environment.h"
#include "symaware/prescan/model/simulation_model.h"

namespace symaware {

class Simulation {
 public:
  Simulation(const Environment& environment);

  Simulation(const Simulation&) = delete;
  Simulation& operator=(const Simulation&) = delete;

  /**
   * @brief Run the simulation automatically for the given amount of @p seconds
   * If @p seconds is negative, the simulation will run indefinitely
   * @note Is mutually exclusive with @ref step and can be called only once.
   * If another simulation needs to be run, create another instance of @ref Simulation
   * @param seconds amount of time to run the simulation. If negative, the simulation will run indefinitely
   */
  void run(double seconds);
  /**
   * @brief Initialise the simulation.
   *
   * This method must be called before running the simulation via @ref step.
   */
  void initialise();
  /**
   * @brief Advance the simulation manually.
   *
   * The simulation will progress by one step each time this method is called.
   * This method must be called after the simulation has been initialised via @ref initialise
   * @note Is mutually exclusive with @ref run
   */
  void step();
  /**
   * @brief Terminate the simulation.
   * @note This method should be called after the simulation has been run via @ref step
   * to clean up the simulation.
   */
  void terminate();

  /**
   * @brief Set the log level of the underlying simulation logger
   * @param log_level log level
   */
  void setLogLevel(prescan::sim::ISimulationLogger::LogLevel log_level);

 private:
  bool is_initialised_;
  const Environment& environment_;
  SimulationModel model_;
  prescan::sim::ManualSimulation simulation_;
};

}  // namespace symaware
