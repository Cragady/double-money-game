cmake_minimum_required(VERSION 3.5)

project(DMG_TESTS LANGUAGES CXX VERSION 0.0.1)

include(catch2Import)

add_executable(tests test.cpp test-main.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2)

include(CTest)
include (Catch)
catch_discover_tests(tests)
