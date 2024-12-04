if (NOT TARGET glfw)
  project(glfw)

  add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/glfw")
endif()
