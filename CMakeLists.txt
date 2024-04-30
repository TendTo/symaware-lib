cmake_minimum_required(VERSION 3.21.0)
set(SKBUILD_PROJECT_NAME
    symaware
    CACHE INTERNAL "Project name")
set(SKBUILD_PROJECT_VERSION
    0.0.1
    CACHE INTERNAL "Project version")
project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD
    17
    CACHE STRING "C++ version selection")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If this is the main app, enable testing, doxygen, and packaging
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)
  # Support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  # If this is the main app, we want to enable testing
  include(CTest)
  enable_testing()
  # If this is the main app, we want to enable doxygen
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
  # If this is the main app, we want to enable packaging
  set(CPACK_PROJECT_NAME ${PROJECT_NAME})
  set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
  include(CPack)
endif()

# Settings

set(Prescan_base_DIR
    "C:/Program Files/Simcenter Prescan/Prescan_2403"
    CACHE STRING "" FORCE)
set(Prescan_DIR "${Prescan_base_DIR}/lib/cmake")
set(Prescan_PATH
    "${Prescan_base_DIR}/bin\\;${Prescan_base_DIR}/Plugins/FullWaveformLidarPlugin/bin\\;${Prescan_base_DIR}/Plugins/PBRadarPlugin/bin\\;${Prescan_base_DIR}/Plugins/PointCloudLidarPlugin/bin\\;${Prescan_base_DIR}/Plugins/ProbabilisticSensorsPlugin/bin\\;${Prescan_base_DIR}/Plugins/V2XPlugin/bin"
)
set(INSTALL_GTEST OFF)

# External dependencies

include(FetchContent)

set(PYBIND11_NEWPYTHON ON)
find_package(Prescan 2024.1 REQUIRED) # Search for Prescan

# fmt library
FetchContent_Declare(
  fmtlib
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1)
# googletest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0)
# pybind11
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.12.0)

FetchContent_MakeAvailable(fmtlib)
FetchContent_MakeAvailable(pybind11)

# Add subdirectories

add_subdirectory(src)
add_subdirectory(python)

# Testing

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  add_subdirectory(tests)
endif()
