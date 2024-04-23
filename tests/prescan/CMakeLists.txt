set(HEADER_LIST "${symaware_SOURCE_DIR}/include/symaware/symaware.h")

add_executable(test_symaware_prescan test_symaware_prescan.cpp ${HEADER_LIST})
target_include_directories(test_symaware_prescan PRIVATE ../include)
target_link_libraries(test_symaware_prescan symaware_prescan)

add_test(NAME TestSymawarePrescan COMMAND test_symaware_prescan)

set_tests_properties(
  TestSymawarePrescan
  PROPERTIES
    ENVIRONMENT_MODIFICATION
    "PATH=path_list_prepend:${Prescan_base_DIR}/bin\\;${Prescan_base_DIR}/Plugins/FullWaveformLidarPlugin/./bin\\;${Prescan_base_DIR}/Plugins/PBRadarPlugin/./bin\\;${Prescan_base_DIR}/Plugins/PointCloudLidarPlugin/./bin\\;${Prescan_base_DIR}/Plugins/ProbabilisticSensorsPlugin/bin\\;${Prescan_base_DIR}/Plugins/V2XPlugin/bin"
)
