if (NOT TARGET raylib)
  find_package(raylib 5.5)

  if (NOT raylib_FOUND)
    # MESSAGE(WARNING "Building raylib, this will make the raylib submodule dirty")
    add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/raylib" ${BUILD_OUTPUT}/raylib)
  endif()
endif()
