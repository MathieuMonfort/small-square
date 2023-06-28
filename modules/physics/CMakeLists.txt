add_library(smallsquare_physics
        source/collision_object.cpp
        source/collision_object.h
        source/collider_object.cpp
        source/collider_object.h
        source/physics_object.cpp
        source/physics_object.h)

target_link_libraries(smallsquare_physics smallsquare_core)
target_include_directories(smallsquare_physics PUBLIC ".")