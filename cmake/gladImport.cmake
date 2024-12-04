if (NOT TARGET glad)
  project(glad)

  # find_package(glfw REQUIRED) # This is not required: built by project

  set(GLAD_SOURCES_DIR "${CMAKE_SOURCE_DIR}/vendor/glad")

  add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)

  glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)

endif()
