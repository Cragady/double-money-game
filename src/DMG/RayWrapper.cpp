#include <raylib.h>
#include <raymath.h>
#include <terminal-colors.h>

#include <iostream>
#include <memory>
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "DMG/RayWrapper.hpp"
#include "DMG/core/GameState.hpp"
#include "DMG/gui/DebugWindow.hpp"
#include "DMG/gui/Scene.hpp"
#include "DMG/gui/scene-creator.hpp"
#include "DMG/raygui/MainCamera.hpp"
#include "imgui.h"
#include "rlImGui.h"

RayWrapper::RayWrapper(GameOptions game_options) {
  screen_width_ = game_options.width;
  screen_height_ = game_options.height;
  target_fps_ = game_options.fps;

  default_camera_ = std::make_shared<MainCamera>();
  debug_window_ = std::make_shared<DebugWindow>();

  scene_creator_ = scenecreator::SceneCreator(default_camera_, debug_window_);

  debug_window_->CopyBoolPtrOne(
      Dw_CbpArgs {.name = "ImGui Demo", .bool_ptr = &imgui_demo_active_});
  debug_window_->SetProgramFlag(
      Dw_CbpArgs {.name = "Reset GUI", .bool_ptr = &reset_gui_});

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
  if (!current_scene_) current_scene_ = scene_creator_.Setup(state);
  if (!current_scene_) return;
  current_scene_->Setup(state, gui_setup_);
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
  if (current_scene_) {
    current_scene_->Update(state);
  }
  if (draw_fps_) {
    DrawFPS(10, 10);
  }
  ImGuiDemo();
}

void RayWrapper::Shutdown(const GameStateUPtr &state) {
  if (!current_scene_) return;
  current_scene_->Shutdown(state);
}

void RayWrapper::ImGuiDemo() {
  if (imgui_demo_active_) ImGui::ShowDemoWindow(&imgui_demo_active_);
}
