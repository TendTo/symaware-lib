import sys
import pybind11_stubgen

if __name__ == '__main__':
    sys.argv = ["pybind11-stubgen", "symaware.prescan._symaware_prescan", "-o", "."]
    pybind11_stubgen.main()
