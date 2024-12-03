cmake_minimum_required(VERSION 3.22)

project(DMG)

set(ImGui_Loaded false)
set(RLImGui_Loaded false)

# Avoid excessive expansion of variables in conditionals. In particular, if
# "PLATFORM" is "DRM" then:
#
# if (${PLATFORM} MATCHES "DRM")
#
# may expand e.g to:
#
# if (/usr/lib/aarch64-linux-gnu/libdrm.so MATCHES "DRM")
#
# See https://cmake.org/cmake/help/latest/policy/CMP0054.html
cmake_policy(SET CMP0054 NEW)

# Makes a hidden visibility preset on a static lib respected
# This is used to hide glfw's symbols from the library exports when building an so/dylib
# See https://cmake.org/cmake/help/latest/policy/CMP0063.html
cmake_policy(SET CMP0063 NEW)

set(BUILD_OUTPUT ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT}/bin)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT})

# Anywhere you see include(...) you can check <root>/cmake for that file
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(RayLibImport)
include(ImGuiImport)
include(RLImGuiImport)

include(CompilerFlags)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

# target_link_libraries(DMG PRIVATE ncurses)
