#include "symaware/prescan/simulator.h"

namespace symaware {

void Simulator::registerSimulationUnits(const prescan::api::experiment::Experiment& experiment,
                                        prescan::sim::ISimulation* simulation){};
void Simulator::initialize(prescan::sim::ISimulation* simulation){};
void Simulator::step(prescan::sim::ISimulation* simulation){};
void Simulator::terminate(prescan::sim::ISimulation* simulation){};

}  // namespace symaware