cmake_minimum_required(VERSION 3.5)

project(DMG_TESTS LANGUAGES CXX VERSION 0.0.1)

include(catch2Import)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(tests test.cpp test-main.cpp)
target_include_directories(tests PRIVATE
  $<BUILD_INTERFACE:${DMG_SOURCES_DIR}/..>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries(tests PRIVATE Catch2::Catch2 DMGlib raylib imgui rlimgui glad_gl_core_33 glfw)

include(CTest)
include (Catch)
catch_discover_tests(tests)
