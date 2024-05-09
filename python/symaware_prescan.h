#include <pybind11/pybind11.h>

#include <sstream>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)
#define REPR_LAMBDA(class_name) [](const class_name &o) { return (std::stringstream{} << o).str(); }

void init_type(pybind11::module_ &);
void init_data(pybind11::module_ &);
void init_model(pybind11::module_ &);
void init_road(pybind11::module_ &);
void init_simulation(pybind11::module_ &);
void init_environment(pybind11::module_ &);
void init_api(pybind11::module_ &);
void init_entity(pybind11::module_ &);
