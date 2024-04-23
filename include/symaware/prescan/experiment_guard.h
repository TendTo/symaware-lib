/**
 * @file experiment_guard.h
 * @author Ernesto Casablanca (casablancaernesto@gmail.com)
 * @copyright 2024
 * @licence Apache-2.0 license
 * @brief ExperimentGuard class
 */
#pragma once

#include <prescan/api/experiment.hpp>

namespace symaware {

/** @brief Guard that uses RAII to save and delete the experiment file */
class ExperimentGuard {
 public:
  /**
   * @brief Construct a new Experiment Guard object and save the experiment file
   * @param experiment experiment object
   */
  ExperimentGuard(prescan::api::experiment::Experiment& experiment);
  /** @brief Destroy the Experiment Guard object and delete the experiment file */
  ~ExperimentGuard();

  ExperimentGuard(const ExperimentGuard&) = delete;
  ExperimentGuard& operator=(const ExperimentGuard&) = delete;

  /**
   * @brief Get the experiment object
   * @return experiment object
   */
  const prescan::api::experiment::Experiment& experiment() const { return experiment_; }

 private:
  const prescan::api::experiment::Experiment& experiment_;  ///< experiment object
};
}  // namespace symaware
