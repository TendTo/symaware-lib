#include "symaware/prescan/experiment_guard.h"

#include <fmt/core.h>

#include <filesystem>

namespace symaware {

ExperimentGuard::ExperimentGuard(prescan::api::experiment::Experiment& experiment) : experiment_(experiment) {
  const std::string filename{std::filesystem::current_path().filename().string() + ".pb"};
  if (std::filesystem::exists(filename)) {
    fmt::print("WARNING: Removing existing experiment file: {}\n", filename);
    std::filesystem::remove(filename);
  }
  experiment.saveToFile(filename);
}
ExperimentGuard::~ExperimentGuard() {
  const std::string filename{std::filesystem::current_path().filename().string() + ".pb"};
  std::filesystem::remove(filename);
}

std::string ExperimentGuard::dirpath() const { return std::filesystem::current_path().string(); }

}  // namespace symaware
