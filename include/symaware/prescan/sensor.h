/**
 * @file sensor.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief Sensor class
 */
#pragma once

#include <memory>
#include <prescan/api/Experiment.hpp>
#include <prescan/api/types/SensorBase.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/CameraSensorUnit.hpp>
#include <prescan/sim/Simulation.hpp>
#include <vector>

#include "symaware/prescan/type.h"

namespace symaware {

class Sensor {
 public:
  Sensor(SensorType sensor_type, bool existing);
  Sensor(SensorType sensor_type, std::vector<double> setup = {}, bool existing = false);
  /**
   * @brief Initialise the sensor attaching it to the @p object upon its initialisation.
   * @param object object the sensor will be attached to
   * @param id id of the sensor among the ones of the same kind attached to the @p object
   */
  void createSensor(const prescan::api::types::WorldObject& object, int id);
  /**
   * @brief Register the sensor.
   *
   * Called at the beginning of the @p simulation.
   * @param experiment experiment about to be run
   * @param simulation simulation that will run the experiment
   */
  void registerUnit(const prescan::api::types::WorldObject& object,
                    const prescan::api::experiment::Experiment& experiment, prescan::sim::ISimulation* simulation);
  /**
   * @brief Initialise the sensor.
   *
   * Called before the first step of the @p simulation.
   * @param simulation simulation that is about to run the experiment
   */
  void initialise(prescan::sim::ISimulation* simulation);
  /**
   * @brief Step the sensor, updating the data avaiable to the sensor's consumer.
   *
   * Called at each step of the @p simulation.
   * @param simulation simulation that is running the experiment
   */
  void step(prescan::sim::ISimulation* simulation);
  /**
   * @brief Terminate the sensor.
   *
   * Called at the end of the @p simulation.
   * @param simulation simulation that has run the experiment
   */
  void terminate(prescan::sim::ISimulation* simulation);

  SensorType sensor_type() const { return sensor_type_; }
  const std::vector<double>& setup() const { return setup_; }
  const std::vector<double>& state() const { return state_; }
  const prescan::sim::CameraSensorUnit::Image& image() const { return image_; }

 private:
  template <class T>
  void applySetup(T* sensor_ptr);
  template <class T>
  void updateState();

  bool existing_;
  int id_;
  SensorType sensor_type_;
  std::vector<double> setup_;
  std::vector<double> state_;
  prescan::sim::CameraSensorUnit::Image image_;
  std::unique_ptr<prescan::sim::Unit> sensor_unit_;
};

}  // namespace symaware
