set(HEADER_LIST "${symaware_SOURCE_DIR}/include/symaware/util.h"
                "${symaware_SOURCE_DIR}/include/symaware/util/exception.h")
set(SOURCE_LIST "")

# libraries
add_library(symaware_util ${SOURCE_LIST} ${HEADER_LIST})

# include directories
target_include_directories(symaware_util PUBLIC ${symaware_SOURCE_DIR}/include)

# link libraries
target_link_libraries(symaware_util fmt::fmt)

# enforce C++11
target_compile_features(symaware_util PUBLIC cxx_std_11)

# output directories
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files for symaware_util"
  FILES ${HEADER_LIST})
