#include "symaware/prescan/experiment_guard.h"

#include <filesystem>

namespace symaware {

ExperimentGuard::ExperimentGuard(prescan::api::experiment::Experiment& experiment) : experiment_(experiment) {
  const std::string base_name{std::filesystem::current_path().filename().string()};
  experiment.saveToFile(base_name + ".pb");
}
ExperimentGuard::~ExperimentGuard() {
  const std::string base_name{std::filesystem::current_path().filename().string()};
  std::filesystem::remove(base_name + ".pb");
}

}  // namespace symaware
