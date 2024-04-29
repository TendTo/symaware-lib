set(SOURCE_LIST "simaware_prescan.cpp")

pybind11_add_module(_symaware_prescan ${SOURCE_LIST})

target_compile_definitions(_symaware_prescan
                           PRIVATE PYBIND11_DETAILED_ERROR_MESSAGES)
target_compile_definitions(_symaware_prescan
                           PRIVATE VERSION_INFO=${SKBUILD_PROJECT_VERSION})

install(TARGETS _symaware_prescan LIBRARY DESTINATION symaware/prescan)
