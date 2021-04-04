cmake_minimum_required(VERSION 3.17)
project(smallsquare)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCURSORDEBUG")

add_subdirectory(include)

add_subdirectory(source/core)

add_subdirectory(samples)


