#include "symaware/prescan/road.h"

namespace symaware {

Road::Road(Environment& environment)
    : Road{const_cast<prescan::api::experiment::Experiment&>(environment.experiment())} {}
Road::Road(prescan::api::experiment::Experiment& experiment) : Road{prescan::api::roads::createRoad(experiment)} {}
Road::Road(prescan::api::roads::types::Road road) : road_(std::move(road)) {}

}  // namespace symaware
