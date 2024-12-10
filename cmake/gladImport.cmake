if (NOT TARGET glad)
  project(glad)

  # find_package(glfw REQUIRED) # This is not required: built by project

  set(CMAKE_CURRENT_BINARY_DIR_BAK ${CMAKE_CURRENT_BINARY_DIR})
  set(CMAKE_CURRENT_BINARY_DIR ${BUILD_OUTPUT})
  set(GLAD_SOURCES_DIR "${CMAKE_SOURCE_DIR}/vendor/glad")

  add_subdirectory("${GLAD_SOURCES_DIR}/cmake" ${BUILD_OUTPUT}/glad_cmake)

  glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)

  set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR_BAK})
  unset(CMAKE_CURRENT_BINARY_DIR_BAK)

endif()
