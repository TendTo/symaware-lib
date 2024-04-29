/**
 * @file dynamical_model.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief DynamicalModel class
 */
#pragma once

#include <prescan/api/experiment/Experiment.hpp>
#include <prescan/api/types/WorldObject.hpp>
#include <prescan/sim/AmesimVehicleDynamicsUnit.hpp>
#include <prescan/sim/Simulation.hpp>
#include <prescan/sim/StateActuatorUnit.hpp>

#include "symaware/prescan/data.h"
#include "symaware/prescan/model/entity_model.h"

namespace symaware {

class DynamicalModel : public EntityModel {
 public:
  /**
   * @brief Construct a new Dynamical Model object with an initial model state.
   * @param state initial model state
   */
  explicit DynamicalModel(DynamicalModelInput initial_input = DynamicalModelInput{false});

  /**
   * @brief Initialise the model by assigning the object in the simulation.
   * @param object simulation object this model will control
   */
  void initialiseObject(prescan::api::experiment::Experiment& experiment, prescan::api::types::WorldObject object);
  /**
   * @brief Set the new control input of the model.
   * @param input model input to set
   */
  void setInput(DynamicalModelInput input);
  /**
   * @brief Use the provided @p input to update the @ref input_ .
   *
   * Only the non-NaN values in the @p input will overwrite the corresponding values in the @ref input_ .
   * @param input model input used to update the current one
   */
  void updateInput(const DynamicalModelInput& input);

  /**
   * @brief Register the unit inside the @p simulaiton.
   *
   * Called at the beginning of the @p simulation.
   * Allows for the model to extract the @ref object_ from the @p simulation
   * and use it to register the @ref state_.
   * @param experiment experiment about to be run
   * @param simulation simulation that will run the experiment
   */
  void registerUnit(const prescan::api::experiment::Experiment& experiment,
                    prescan::sim::ISimulation* simulation) override;

  const DynamicalModelInput& input() const { return input_; }

 private:
  /**
   * @brief Use the @ref state_input_ to update the @ref state_ .
   *
   * Any `NaN` values in the @ref state_input_ are ignored
   * and the corresponding values in the @ref state_ are not changed.
   */
  void updateState() override;

  prescan::sim::AmesimVehicleDynamicsUnit* dynamics_;  ///< The dynamics of the entity in the simulation
  DynamicalModelInput input_;                          ///< The model state of the entity that will be applied each step
};

}  // namespace symaware
