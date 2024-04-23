# Symaware

Library extension to allow the python package [Symaware]() to efficiently connect to external simulators that expose c++ API's.

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
