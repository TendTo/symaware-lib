# Symaware

Library extension to allow the python package [Symaware]() to efficiently connect to external simulators that expose c++ API's.

## Requirements

- [Prescan (2024.1)](https://www.plm.automation.siemens.com/global/en/products/simcenter/prescan.html)
- [Python 3.9+](https://www.python.org/downloads/)
- [CMake 3.21+](https://cmake.org/download/)
- c++ compiler
    - [mingw-w64](https://sourceforge.net/projects/mingw-w64/) **Tested**
    - [MSYS2](https://www.msys2.org/) **Untested**
    - [Visual Studio 2019+](https://visualstudio.microsoft.com/) **Untested**

## Installation

## Use

### Ensuring the `PATH` is set correctly

The executable needs some shared libraries (`ddls`) to be in the `PATH` environment variable. This can be done by using the following code snippet in the powershell console before running executable:

```powershell
$prescan_dir = "C:/Program Files/Simcenter Prescan/Prescan_2403"
$env:PATH += ";$prescan_dir/bin;$prescan_dir/Plugins/FullWaveformLidarPlugin/./bin;$prescan_dir/Plugins/PBRadarPlugin/./bin;$prescan_dir/Plugins/PointCloudLidarPlugin/./bin;$prescan_dir/Plugins/ProbabilisticSensorsPlugin/bin;$prescan_dir/Plugins/V2XPlugin/bin"
```

Or, in the command prompt:

```bat
set prescan_dir=C:/Program Files/Simcenter Prescan/Prescan_2403
set PATH=%PATH%;%prescan_dir%/bin;%prescan_dir%/Plugins/FullWaveformLidarPlugin/./bin;%prescan_dir%/Plugins/PBRadarPlugin/./bin;%prescan_dir%/Plugins/PointCloudLidarPlugin/./bin;%prescan_dir%/Plugins/ProbabilisticSensorsPlugin/bin;%prescan_dir%/Plugins/V2XPlugin/bin
```

### Ensuring the `PATH` is set correctly for Python

The executable needs some shared libraries (`ddls`) to be in the `PATH` environment variable. This can be done by using the following code snippet in the powershell console before running executable:

```powershell
$prescan_dir = "C:/Program Files/Simcenter Prescan/Prescan_2403"
$env:PYTHONPATH += ";$prescan_dir/python"
$env:PATH += ";$prescan_dir/bin"
```

Or, in the command prompt:

```bat
set prescan_dir=C:/Program Files/Simcenter Prescan/Prescan_2403
set PYTHONPATH=%PYTHONPATH%;%prescan_dir%\python
set PATH=%PATH%;%prescan_dir%\bin
```

### Build python bindings

```powershell
python3.11.exe -m pip uninstall symaware-prescan symaware-base -y ; rm  -r -fo 'C:\msys64\mingw64\lib\python3.11\site-packages\symaware' ; python3.11.exe -m pip install . --index-url https://gitlab.mpi-sws.org/api/v4/projects/2668/packages/pypi/simple ; python3.11.exe .\script\stubs.py ; cp .\python\symaware\prescan\_symaware_prescan.pyi 'C:\msys64\mingw64\lib\python3.11\site-packages\symaware\prescan'
```


## Dependecy graph

```mermaid
flowchart TD
    sim[ManualSimulator]
    sim_mod[SimulatorModel]
    dynamical_model1[DynamicalModel]
    dynamical_model2[DynamicalModel]
    dynamical_model3[DynamicalModel]
    env[Evironment]
    exp[Experiment]
    exp_guard[ExperimentGuard]

sim --> sim_mod
sim --> env
sim --> exp_guard
sim_mod --> dynamical_model1
sim_mod --> dynamical_model2
sim_mod --> dynamical_model3
env --> exp
dynamical_model1 --> exp
dynamical_model2 --> exp
dynamical_model3 --> exp
exp_guard --> exp
```

```mermaid
sequenceDiagram
    actor user as User

note right of user : Initialise the environment

create participant env as Environment

user ->> env : new

create participant sim_mod as SimulatorModel
env ->> sim_mod : new

create participant sim as ManualSimulator
env ->> sim : new 

create participant exp as Experiment
env ->> exp : new

note over user, env : Change experiment setup (weather, time, etc.)

user ->>+ env : setup
env ->>+ exp : setup
deactivate env
deactivate exp

note over user, env : Add agent to the experiment

create participant dyn as DynamicalModel
user -> dyn : new
create participant ent2 as Entity
user ->> ent2 : new(dynamic_model) // the dynamic model can be a nullptr
user ->>+ env : addEntity(entity) (via reference)
env ->>+ exp : createObject(entity.type)
exp -->- env : object
env ->>+ ent2 : initialise(object)
deactivate ent2
env -->- user : entity (updated)



```
