#include "symaware_prescan.h"

namespace py = pybind11;

PYBIND11_MODULE(_symaware_prescan, m) {
  init_data(m);
  init_road(m);
  // init_environment(m);

  m.doc() = "Python binding for the symaware prescan library";
#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
#error "VERSION_INFO is not defined"
#endif
  // Fest
}
