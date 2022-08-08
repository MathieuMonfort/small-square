set(RESOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_executable(sample main.cpp)

target_link_libraries(sample PRIVATE smallsquare_core smallsquare_ui)