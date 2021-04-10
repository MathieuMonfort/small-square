
find_package(Catch2 REQUIRED)

add_executable(UnitTests testconfig.h)
SET_TARGET_PROPERTIES(UnitTests PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(UnitTests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(UnitTests Catch2::Catch2)