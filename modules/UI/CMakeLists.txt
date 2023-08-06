set(UI_HEADERS
        source/canvas.h
        source/ui_quad.h
        )

add_library(small-square_ui
        source/canvas.cpp
        source/ui_quad.cpp

        ${UI_HEADERS}
        )

target_link_libraries(small-square_ui small-square_core)
target_include_directories(small-square_ui PUBLIC ".")

install(TARGETS small-square_ui
        DESTINATION lib64/small-square/)
install(FILES ${UI_HEADERS}
        DESTINATION include/small-square/UI)