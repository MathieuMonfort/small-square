add_library(smallsquare_physics
        collision_object.cpp
        collision_object.h
        collider_object.cpp
        collider_object.h
        physics_object.cpp
        physics_object.h)

target_link_libraries(smallsquare_physics smallsquare_core)
target_include_directories(smallsquare_physics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")