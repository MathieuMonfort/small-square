set(RESOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_executable(small-square_sample main.cpp)

target_link_libraries(small-square_sample PRIVATE small-square_core small-square_ui small-square_physics)