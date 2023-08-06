set(PHYSICS_HEADERS
        source/collision_object.h
        source/collider_object.h
        source/physics_object.h
        )

add_library(small-square_physics
        source/collision_object.cpp
        source/collider_object.cpp
        source/physics_object.cpp
        ${PHYSICS_HEADERS}
        )
target_link_libraries(small-square_physics small-square_core)
target_include_directories(small-square_physics PUBLIC ".")

install(TARGETS small-square_physics
        DESTINATION lib64/small-square)
install(FILES ${PHYSICS_HEADERS}
        DESTINATION include/small-square/physics)