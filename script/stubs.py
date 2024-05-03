import sys
import os
import pybind11_stubgen


PRESCAN_DIR = "C:/Program Files/Simcenter Prescan/Prescan_2403"

if __name__ == "__main__":
    os.add_dll_directory(f"{PRESCAN_DIR}/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/FullWaveformLidarPlugin/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/PBRadarPlugin/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/PointCloudLidarPlugin/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/ProbabilisticSensorsPlugin/bin")
    os.add_dll_directory(f"{PRESCAN_DIR}/Plugins/V2XPlugin/bin")

    dir_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "..", "python")
    print(dir_path)
    sys.argv = ["pybind11-stubgen", "symaware.simulators.prescan._symaware_prescan", "-o", str(dir_path)]

    pybind11_stubgen.main()

    file_path = os.path.join(
        dir_path,
        "symaware",
        "simulators",
        "prescan",
        "_symaware_prescan.pyi",
    )
    with open(file_path, "r") as file:
        filedata = file.read()

    filedata = (
        filedata.replace("float = ...", "float = float('inf')")
        .replace("entity: ...", "entity: '_Entity'")
        .replace(
            "def add_entity(self, name: str, entity_model: _EntityModel = None) -> ...:",
            "def add_entity(self, name: str, entity_model: _EntityModel = None) -> _Entity:",
        )
        .replace(
            "def add_road(self, position: Position = ...) -> ...:",
            "def add_road(self, position: Position = None) -> Road:",
        )
        .replace("def road(self) -> ...:", "def road(self) -> Road:")
        .replace("def state(self) -> ...:", "def state(self) -> State:")
    )

    with open(file_path, "w") as file:
        file.write(filedata)
