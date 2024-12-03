# file(GLOB_RECURSE DMG_SOURCES CONFIGURE_DEPENDS "*.cpp")
# file(GLOB_RECURSE DMG_HEADERS CONFIGURE_DEPENDS "*.hpp")

set (DMG_SOURCES
  main.cpp
  RandomChance/RandomChance.cpp
  RaylibStarter/ImageViewerWindow.cpp
  RaylibStarter/SceneViewWindow.cpp
  RaylibStarter/Demo.cpp
)

set (DMG_HEADERS
  main.hpp
  RandomChance/RandomChance.hpp
  RaylibStarter/DocumentWindow.hpp
  RaylibStarter/ImageViewerWindow.hpp
  RaylibStarter/SceneViewWindow.hpp
  RaylibStarter/Demo.hpp
)

set(DMG_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")
foreach(_headerFile ${DMG_HEADERS})
  get_filename_component(_dir ${_headerFile} PATH)
  list(APPEND DMG_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES DMG_INCLUDE_DIRS)

include_directories(${CMAKE_SOURCE_DIR}/include)
# link_directories("${CMAKE_SOURCE_DIR}/lib/gcc")

# add_library(glfw3 SHARED IMPORTED)
# set_target_properties(glfw3 PROPERTIES
#   IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/gcc/libglfw.so"
#   # INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include/GLFW"
# )
#
# add_library(cglm SHARED IMPORTED)
# set_target_properties(cglm PROPERTIES
#   IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/cglm/libcglm.so"
# )

add_executable(DMG ${DMG_SOURCES})
target_include_directories(DMG PRIVATE ${DMG_INCLUDE_DIRS})
target_link_libraries(DMG raylib imgui rlimgui)
# target_link_libraries(DMG Xrander)
# target_link_libraries(DMG glfw3 cglm GL X11 pthread Xi dl)
set_target_properties(DMG PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT})

# add_custom_command(
#   TARGET DMG
#   POST_BUILD
#   COMMAND DMG
# )
