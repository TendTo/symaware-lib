add_subdirectory(prescan)
add_subdirectory(util)

set(HEADER_LIST "${symaware_SOURCE_DIR}/include/symaware/symaware.h")

add_executable(main main.cpp ${HEADER_LIST})

target_include_directories(main PRIVATE ../include)

target_link_libraries(main symaware_prescan)
target_link_libraries(main symaware_util)

prescan_generate_helper_scripts(TARGET main)
