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

