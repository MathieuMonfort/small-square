cmake_minimum_required(VERSION 3.17)
project(smallsquare)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCURSOR_DEBUG")

add_subdirectory(include)

add_subdirectory(source/core)
add_subdirectory(source/UI)


#add_subdirectory(unit-tests)


add_subdirectory(samples)


