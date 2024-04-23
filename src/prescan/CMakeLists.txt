set(HEADER_LIST
    "${symaware_SOURCE_DIR}/include/symaware/prescan.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/environment.h"
    "${symaware_SOURCE_DIR}/include/symaware/prescan/simulator.h")
set(SOURCE_LIST "${symaware_SOURCE_DIR}/src/prescan/simulator.cpp"
                "${symaware_SOURCE_DIR}/src/prescan/environment.cpp")

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
