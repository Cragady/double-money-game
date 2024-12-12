if (NOT TARGET raylib)
    add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/raylib" ${BUILD_OUTPUT}/raylib)
endif()
