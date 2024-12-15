# file(GLOB_RECURSE DMG_SOURCES CONFIGURE_DEPENDS "*.cpp")
# file(GLOB_RECURSE DMG_HEADERS CONFIGURE_DEPENDS "*.hpp")

set (DMG_SOURCES
  ${DMG_SOURCES_DIR}/Game.cpp
  ${DMG_SOURCES_DIR}/RayWrapper.cpp
  ${DMG_SOURCES_DIR}/core/GameState.cpp
  ${DMG_SOURCES_DIR}/core/RandomTracker.cpp
  ${DMG_SOURCES_DIR}/core/RandomChance.cpp
  ${DMG_SOURCES_DIR}/core/input/KeyboardInput.cpp
  ${DMG_SOURCES_DIR}/core/events/event-functions.cpp
  ${DMG_SOURCES_DIR}/core/util/color-conversion.cpp
  ${DMG_SOURCES_DIR}/core/util/ColorShifting.cpp
  ${DMG_SOURCES_DIR}/raygui/GuiManager.cpp
  ${DMG_SOURCES_DIR}/raygui/MainCamera.cpp
  ${DMG_SOURCES_DIR}/raygui/RayButton.cpp
  ${DMG_SOURCES_DIR}/gui/DebugWindow.cpp
  ${DMG_SOURCES_DIR}/gui/StatsWindow.cpp
  ${DMG_SOURCES_DIR}/gui/Scene.cpp
  ${DMG_SOURCES_DIR}/gui/SceneManager.cpp
  ${DMG_SOURCES_DIR}/gui/scene-creator.cpp
  ${DMG_SOURCES_DIR}/gui/element/Button.cpp
  # ${DMG_SOURCES_DIR}/gui/element/ShaderButton.cpp
  ${DMG_SOURCES_DIR}/gui/element/TextElement.cpp
  ${DMG_SOURCES_DIR}/gui/examples/ImGuiMyFirstTool.cpp
  ${DMG_SOURCES_DIR}/vendor/util/raylib-text-draw-3d.cpp
  ${DMG_SOURCES_DIR}/vendor/ImageViewerWindow.cpp
  ${DMG_SOURCES_DIR}/vendor/SceneViewWindow.cpp
  ${DMG_SOURCES_DIR}/vendor/RlImGuiDemo.cpp
)

set (DMG_HEADERS
  ${DMG_SOURCES_DIR}/Game.hpp
  ${DMG_SOURCES_DIR}/GameOptions.hpp
  ${DMG_SOURCES_DIR}/RayWrapper.hpp
  ${DMG_SOURCES_DIR}/core/GameState.hpp
  ${DMG_SOURCES_DIR}/core/RandomTracker.hpp
  ${DMG_SOURCES_DIR}/core/RandomChance.hpp
  ${DMG_SOURCES_DIR}/core/ICoreBase.hpp
  ${DMG_SOURCES_DIR}/core/IGui.hpp
  ${DMG_SOURCES_DIR}/core/IGuiManager.hpp
  ${DMG_SOURCES_DIR}/core/input/KeyboardInput.hpp
  ${DMG_SOURCES_DIR}/core/events/event-functions.hpp
  ${DMG_SOURCES_DIR}/core/util/color-conversion.hpp
  ${DMG_SOURCES_DIR}/core/util/ColorShifting.hpp
  ${DMG_SOURCES_DIR}/raygui/GuiManager.hpp
  ${DMG_SOURCES_DIR}/raygui/MainCamera.hpp
  ${DMG_SOURCES_DIR}/raygui/RayButton.hpp
  ${DMG_SOURCES_DIR}/gui/IWindow.hpp
  ${DMG_SOURCES_DIR}/gui/DebugWindow.hpp
  ${DMG_SOURCES_DIR}/gui/StatsWindow.hpp
  ${DMG_SOURCES_DIR}/gui/Scene.hpp
  ${DMG_SOURCES_DIR}/gui/SceneManager.hpp
  ${DMG_SOURCES_DIR}/gui/scene-creator.hpp
  ${DMG_SOURCES_DIR}/gui/element/Button.hpp
  # ${DMG_SOURCES_DIR}/gui/element/ShaderButton.hpp
  ${DMG_SOURCES_DIR}/gui/element/TextElement.hpp
  ${DMG_SOURCES_DIR}/gui/examples/ImGuiMyFirstTool.hpp
  ${DMG_SOURCES_DIR}/vendor/util/raylib-text-draw-3d.cpp
  ${DMG_SOURCES_DIR}/vendor/ImageViewerWindow.hpp
  ${DMG_SOURCES_DIR}/vendor/SceneViewWindow.hpp
  ${DMG_SOURCES_DIR}/vendor/RlImGuiDemo.hpp
)

set(DMG_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")
# foreach(_headerFile ${DMG_HEADERS})
#   get_filename_component(_dir ${_headerFile} PATH)
#   list(APPEND DMG_INCLUDE_DIRS ${_dir})
# endforeach()
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

add_library(DMGlib ${DMG_HEADERS} ${DMG_SOURCES})
target_include_directories(DMGlib
  PUBLIC
  $<BUILD_INTERFACE:${DMG_SOURCES_DIR}/..>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries(DMGlib raylib imgui rlimgui glad_gl_core_33 glfw glm::glm)

add_executable(DMG main.cpp)
target_link_libraries(DMG DMGlib)
target_include_directories(DMG PUBLIC ${DMG_INCLUDE_DIRS})
# target_link_libraries(DMG Xrander)
# target_link_libraries(DMG glfw3 cglm GL X11 pthread Xi dl)
set_target_properties(DMG PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT})

project(rlimgui_editor_example)

add_executable(rlimgui_editor_example DMG/vendor/editor.cpp)
target_include_directories(rlimgui_editor_example PRIVATE ${DMG_INCLUDE_DIRS})
target_link_libraries(rlimgui_editor_example raylib imgui rlimgui glad_gl_core_33 glfw)
# target_link_libraries(rlimgui_editor_example Xrander)
# target_link_libraries(rlimgui_editor_example glfw3 cglm GL X11 pthread Xi dl)
set_target_properties(rlimgui_editor_example PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT})

# add_custom_command(
#   TARGET DMG
#   POST_BUILD
#   COMMAND DMG
# )
