cmake_minimum_required(VERSION 3.17)
project(smallsquare)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCURSOR_DEBUG")
set(FIND_LIBRARY_USE_LIB64_PATHS True)

include_directories(core/include)
include_directories(core/source)

add_subdirectory("core")

if(DEFINED SQ_MODULES)
    if(SQ_MODULES MATCHES "UI" OR SQ_MODULES MATCHES "all")
        include_directories(modules/UI/source)
        add_subdirectory(modules/UI)
    endif()
    if(SQ_MODULES MATCHES "physics" OR SQ_MODULES MATCHES "all")
        include_directories(modules/physics/source)
        add_subdirectory(modules/physics)
    endif()
endif()

if(BUILD_SAMPLES)
    add_subdirectory(samples)
endif()

message("Doxygen Doc Configuration")

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXY_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen/doxygen.in)
    set(DOXY_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen/doxygen.out)

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen/)
    configure_file(${DOXY_IN} ${DOXY_OUT} @ONLY)

    add_custom_target(doxygen
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXY_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Building Doxygen API Doc"
            VERBATIM
            )

else(DOXYGEN_FOUND)
    message("Doxygen not installed")
endif(DOXYGEN_FOUND)
