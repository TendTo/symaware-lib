import os

PRESCAN_DIR = "C:/Program Files/Simcenter Prescan/Prescan_2403"
os.add_dll_directory(f"{PRESCAN_DIR}/bin")
os.environ["PATH"] = f"{PRESCAN_DIR}/bin;{os.environ['PATH']}"
