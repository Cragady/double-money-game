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
include(glfwImport)
include(gladImport)

include(CompilerFlags)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src ${BUILD_OUTPUT}/DMG_SRC)

add_subdirectory(test ${BUILD_OUTPUT}/test)

add_custom_target(
  test
  COMMAND tests
)

add_custom_target(
  verbose-test
  COMMAND tests -s
)

add_custom_target(
  run
  COMMAND DMG
)

add_custom_target(
  val
  COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=${CMAKE_SOURCE_DIR}/log/valgrind.log ${CMAKE_SOURCE_DIR}/build/DMG
)

add_custom_target(
  og
  COMMAND gcc ${CMAKE_SOURCE_DIR}/ref/double-money-game.c -Iinclude -Wall -Wpedantic -Werror -o ${CMAKE_SOURCE_DIR}/build/og.out
)

add_custom_target(
  print-test
  COMMAND gcc ${CMAKE_SOURCE_DIR}/ref/terminal-print-test.c -Iinclude -Wall -Wpedantic -Werror -o ${CMAKE_SOURCE_DIR}/build/print-test.out
)

add_custom_target(
  alt-all
  COMMAND make og
  COMMAND make print-test
)

add_custom_target(
  run-og
  COMMAND ${CMAKE_SOURCE_DIR}/build/og.out
)

add_custom_target(
  run-print-test
  COMMAND ${CMAKE_SOURCE_DIR}/build/print-test.out
)

add_custom_target(
  ultra-clean
  COMMAND rm -rf ${CMAKE_SOURCE_DIR}/build/*
)

add_custom_target(
  git-clean
  COMMAND git clean -ndfX
  COMMAND echo "run \\\"git clean -dfX\\\" if you are OK with deleting the listed files"
)
# target_link_libraries(DMG PRIVATE ncurses)
