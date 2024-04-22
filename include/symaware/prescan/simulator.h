#pragma once

#include <prescan/sim/ISimulationModel.hpp>

namespace symaware {

class Simulator : public prescan::sim::ISimulationModel {
 public:
  Simulator() = default;
  void registerSimulationUnits(const prescan::api::experiment::Experiment& experiment,
                               prescan::sim::ISimulation* simulation) override;
  void initialize(prescan::sim::ISimulation* simulation) override;
  void step(prescan::sim::ISimulation* simulation) override;
  void terminate(prescan::sim::ISimulation* simulation) override;

 private:
  // prescan::sim::StateActuatorUnit* m_egoStateUnit;
  // prescan::sim::SelfSensorUnit* m_egoSelfUnit;
  // prescan::sim::PathUnit* m_pathUnit;
  // prescan::sim::SpeedProfileUnit* m_speedProfileUnit;
  // prescan::sim::AirSensorUnit* m_airSensorUnit;
  // prescan::sim::CameraSensorUnit* m_cameraSensorUnit;
};

}  // namespace symaware
