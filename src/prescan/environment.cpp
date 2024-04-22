#include "symaware/prescan/environment.h"

#include <iostream>
#include <prescan/api/experiment.hpp>

namespace symaware {

Environment::Environment() {
  prescan::api::experiment::Experiment experiment = prescan::api::experiment::createExperiment();
  std::cout << experiment << std::endl;
  std::cout << "Environment created" << std::endl;
}

}  // namespace symaware