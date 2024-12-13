project(raylib-examples)
# set(RAYLIB_LIBS "raylib GL X11 Xrandr Xinerama Xi Xxf86vm Xcursor m pthread dl rt glfw")
set(RAYLIB_LIBS "raylib")

link_directories(${BUILD_DIR}/lib)

add_executable(raylib-shaders-hybrid-rendering examples/raylib-shaders-hybrid-rendering.c)
target_link_libraries(raylib-shaders-hybrid-rendering ${RAYLIB_LIBS})

add_executable(raylib-box-collision-example examples/raylib-box-collisions.c)
target_link_libraries(raylib-box-collision-example ${RAYLIB_LIBS})

add_executable(raylib-text-draw-3d-example examples/raylib-text-draw-3d-example.c)
target_link_libraries(raylib-text-draw-3d-example ${RAYLIB_LIBS})
