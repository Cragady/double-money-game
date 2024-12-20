#include <raylib.h>
#include <raymath.h>
#include <terminal-colors.h>

#include <iostream>
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "DMG/RayWrapper.hpp"
#include "DMG/core/GameState.hpp"
#include "DMG/gui/SceneManager.hpp"
#include "DMG/gui/scene-creator.hpp"
#include "rlImGui.h"

RayWrapper::RayWrapper(GameOptions game_options) {
  screen_width_ = game_options.width;
  screen_height_ = game_options.height;
  target_fps_ = game_options.fps;

  glfw_ready_ = glfwInit();
  if (!glfw_ready_) {
    std::cout << TERM_RED "\nGLFW is not able to be used!\n" TERM_CRESET
              << std::endl;
  } else {
    std::cout << TERM_GRN "\nGLFW is now ready!\n" TERM_CRESET << std::endl;
  }
  // TODO: implement when wanted
  // SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(screen_width_, screen_height_, game_options.name.c_str());
  // InitAudioDevice();
  // TODO: implement when wanted
  // SetTargetFPS(target_fps_);

  rlImGuiSetup(true);
  // NOTE: The below will disable movement from click/dragging on imgui window
  // ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
  SetExitKey(KEY_NULL);
  GLFWwindow *window = (GLFWwindow *)GetWindowHandle();
  // glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
  glfwSetWindowSize(window, screen_width_, screen_height_);
}

RayWrapper::~RayWrapper() {
  std::cout << TERM_RED "Shutting Down" TERM_CRESET << std::endl;
  rlImGuiShutdown();
  CloseWindow();
}

void RayWrapper::Setup(const GameStateUPtr &state, bool) {
  state->screen_width_ = screen_width_;
  state->screen_height_ = screen_height_;
  // TODO: make reactive to startup
  state->is_debug_active_ = true;

  scene_manager_.Setup(state, gui_setup_);

  gui_setup_ = true;
}

void RayWrapper::StartOfLoop() {
  BeginDrawing();
  ClearBackground(DARKGRAY);
  rlImGuiBegin();
}

void RayWrapper::EndOfLoop() {
  rlImGuiEnd();
  EndDrawing();
}

void RayWrapper::Loop(const GameStateUPtr &state) {
  hard_stop_ |= WindowShouldClose();
  if (!hard_stop_) {
    StartOfLoop();

    Update(state);

    EndOfLoop();
  }
}

void RayWrapper::Update(const GameStateUPtr &state) {
  if (key_input_.EscapeSequence()) {
    hard_stop_ = true;
  }
  state->screen_width_ = screen_width_;
  state->screen_height_ = screen_height_;
  draw_fps_ = state->draw_fps_;
  scene_manager_.Update(state);
  reset_gui_ = scene_manager_.reset_gui_;
  if (draw_fps_) {
    DrawFPS(10, 10);
  }
}

void RayWrapper::Shutdown(const GameStateUPtr &state) {
  scene_manager_.Shutdown(state);
}
