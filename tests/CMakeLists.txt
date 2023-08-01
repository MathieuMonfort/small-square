set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/core/source)
add_executable(smallsquare_core_tests t_game.cpp)
set_target_properties(smallsquare_core_tests PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(smallsquare_core_tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} smallsquare_core)


#add_test(tester tester)