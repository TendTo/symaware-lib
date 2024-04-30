set(SOURCE_LIST
    "symaware_prescan.cpp"
    "symaware_prescan_data.cpp"
    "symaware_prescan_environment.cpp"
    "symaware_prescan_simulation.cpp"
    "symaware_prescan_model.cpp"
    "symaware_prescan_api.cpp"
    "symaware_prescan_entity.cpp"
    "symaware_prescan_road.cpp")
set(HEADER_LIST "symaware_prescan.h")

pybind11_add_module(_symaware_prescan ${SOURCE_LIST} ${HEADER_LIST})

target_link_libraries(_symaware_prescan PUBLIC symaware_prescan)

target_compile_definitions(_symaware_prescan
                           PRIVATE PYBIND11_DETAILED_ERROR_MESSAGES)
target_compile_definitions(_symaware_prescan
                           PRIVATE VERSION_INFO=${SKBUILD_PROJECT_VERSION})

install(TARGETS _symaware_prescan LIBRARY DESTINATION symaware/prescan)
