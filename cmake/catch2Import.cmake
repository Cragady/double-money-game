if (NOT TARGET Catch2)

  set(catch2_SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/Catch2")
  # list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")

  add_subdirectory("${catch2_SOURCE_DIR}" ${BUILD_OUTPUT}/Catch2)

endif()
