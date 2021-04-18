

add_library(smallsquare_core
                data_tree.h
                game.h
                shader.h
                model.h
                light.h
                texture.h
                camera.h
                debug.h

                game.cpp
                model.cpp
                shader.cpp
                texture.cpp
                camera.cpp
        camera_controller.cpp camera_controller.h
        input.cpp input.h ../UI/canvas.cpp ../UI/canvas.h raycast.cpp raycast.h)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(assimp REQUIRED)
find_package(ZLIB REQUIRED)

target_link_libraries(smallsquare_core PRIVATE 
                            stb_image 
                            glad 
                            OpenGL::GL 
                            glfw 
                            assimp
                            ZLIB::ZLIB)


target_include_directories(smallsquare_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
