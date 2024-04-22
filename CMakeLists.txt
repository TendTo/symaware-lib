cmake_minimum_required(VERSION 3.12.0)
project(
  symaware
  VERSION 0.1.0
  LANGUAGES C CXX)

# If this is the main app, enable testing, doxygen, and packaging
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)
  # Support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  # If this is the main app, we want to enable testing
  include(CTest)
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

# External dependencies

include(FetchContent)

set(Prescan_base_DIR "C:/Program Files/Simcenter Prescan/Prescan_2403")
set(Prescan_DIR "${Prescan_base_DIR}/lib/cmake")

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

set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(fmtlib)
FetchContent_MakeAvailable(googletest)

# Add subdirectories

add_subdirectory(src)

# Testing

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
