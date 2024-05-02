import sys
import os
import pybind11_stubgen


PRESCAN_DIR = "C:/Program Files/Simcenter Prescan/Prescan_2403"

if __name__ == '__main__':
    os.add_dll_directory(f"{PRESCAN_DIR}/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/FullWaveformLidarPlugin/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/PBRadarPlugin/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/PointCloudLidarPlugin/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/ProbabilisticSensorsPlugin/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/V2XPlugin/bin")

    file_path = os.path.dirname(os.path.realpath(__file__))
    print(file_path)
    sys.argv = ["pybind11-stubgen", "symaware.simulators.prescan._symaware_prescan", "-o", f"{file_path}/../python"]

    pybind11_stubgen.main()
