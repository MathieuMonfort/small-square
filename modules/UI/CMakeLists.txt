add_library(smallsquare_ui
        source/canvas.h
        source/canvas.cpp
        source/ui_quad.cpp
        source/ui_quad.h)

target_link_libraries(smallsquare_ui smallsquare_core)
target_include_directories(smallsquare_ui PUBLIC ".")