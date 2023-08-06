set(CORE_HEADERS
        data_tree.h
        game.h
        shader.h
        model.h
        light.h
        texture.h
        camera.h
        debug.h
        camera_controller.h
        input.h
        raycast.h
        gameobject.h
        )




add_library(small-square_core
        game.cpp
        model.cpp
        shader.cpp
        texture.cpp
        camera.cpp
        camera_controller.cpp
        input.cpp
        raycast.cpp
        debug.cpp
        light.cpp
        gameobject.cpp
        ${CORE_HEADERS}
        )

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(assimp REQUIRED)
find_package(ZLIB REQUIRED)

target_link_libraries(small-square_core PRIVATE
                            stb_image 
                            glad 
                            OpenGL::GL 
                            glfw 
                            assimp
                            ZLIB::ZLIB)


target_include_directories(small-square_core PUBLIC "../../source/core")
target_include_directories(small-square_core PUBLIC "../../source/include")

target_link_libraries(small-square_core PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})

install(TARGETS small-square_core
        DESTINATION lib64/small-square
        )

install(FILES ${CORE_HEADERS}
        DESTINATION include/small-square/core
        )

