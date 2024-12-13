if (NOT TARGET raylib)
    set(VENDOR_RAYLIB_DIR "${CMAKE_SOURCE_DIR}/vendor/raylib")
    add_subdirectory(${VENDOR_RAYLIB_DIR} ${BUILD_OUTPUT}/raylib)

    file(COPY "${VENDOR_RAYLIB_DIR}/examples/shaders/resources/shaders" DESTINATION "${CMAKE_SOURCE_DIR}/assets/vendor/raylib")
endif()
