add_library(smallsquare_ui
        canvas.h
        canvas.cpp
        ui_quad.cpp
        ui_quad.h)

target_link_libraries(smallsquare_ui smallsquare_core)
target_include_directories(smallsquare_ui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")