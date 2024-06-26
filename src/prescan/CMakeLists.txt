set(HEADER_LIST
    "${symaware_SOURCE_DIR}/include/symaware/prescan.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/environment.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/experiment_guard.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/simulation.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/sensor.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/entity.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/type.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/data.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/road.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/model/entity_model.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/model/amesim_dynamical_model.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/model/custom_dynamical_model.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/model/track_model.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/model/simulation_model.h")
set(SOURCE_LIST
    "${symaware_SOURCE_DIR}/src/prescan/environment.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/experiment_guard.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/simulation.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/sensor.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/entity.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/data.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/type.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/road.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/model/entity_model.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/model/amesim_dynamical_model.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/model/custom_dynamical_model.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/model/track_model.cpp"
    "${symaware_SOURCE_DIR}/src/prescan/model/simulation_model.cpp")

# libraries
add_library(symaware_prescan ${SOURCE_LIST} ${HEADER_LIST})

# include directories
target_include_directories(symaware_prescan
                           PUBLIC ${symaware_SOURCE_DIR}/include)

# link libraries
target_link_libraries(symaware_prescan Prescan::Prescan)
target_link_libraries(symaware_prescan symaware_util)

# enforce C++11
target_compile_features(symaware_prescan PUBLIC cxx_std_11)

# output directories
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files for symaware_prescan"
  FILES ${HEADER_LIST})
