#include <iostream>

#include <raylib.h>
#include <raymath.h>
#include <terminal-colors.h>
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "RayWrapper.hpp"
#include "imgui.h"
#include "rlImGui.h"

RayWrapper::RayWrapper(GameOptions game_options) {
  screen_width_ = game_options.width;
  screen_height_ = game_options.height;
  target_fps_ = game_options.fps;

  std::shared_ptr<DebugWindow> debug_window_ = window_manager_.debug_window_;
  debug_window_->CopyBoolPtrOne(
      Dw_CbpArgs{.name = "ImGui Demo", .bool_ptr = &imgui_demo_active_});
  debug_window_->SetProgramFlag(
      Dw_CbpArgs{.name = "Reset GUI", .bool_ptr = &reset_gui_});

  glfw_ready_ = glfwInit();
  if (!glfw_ready_) {
    std::cout << TERM_RED "\nGLFW is not able to be used!\n" TERM_CRESET
              << std::endl;
  } else {
    std::cout << TERM_GRN "\nGLFW is now ready!\n" TERM_CRESET << std::endl;
  }
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(screen_width_, screen_height_, game_options.name.c_str());
  SetTargetFPS(target_fps_);

  rlImGuiSetup(true);
  // NOTE: The below will disable movement from click/dragging on imgui window
  // ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
  SetExitKey(KEY_NULL);
  GLFWwindow *window = (GLFWwindow *)GetWindowHandle();
  // glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
  glfwSetWindowSize(window, screen_width_, screen_height_);
  window_manager_.Setup();
  Loop();
}

RayWrapper::~RayWrapper() {
  std::cout << TERM_RED "Shutting Down" TERM_CRESET << std::endl;
  window_manager_.Shutdown();
  rlImGuiShutdown();
  CloseWindow();
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

void RayWrapper::Loop() {
  hard_stop_ |= WindowShouldClose();
  if (!hard_stop_) {
    StartOfLoop();

    Update();

    EndOfLoop();
  }
}

void RayWrapper::Update() {
  if (key_input_.EscapeSequence()) {
    hard_stop_ = true;
  }
  window_manager_.Update();
  ImGuiDemo();
}

void RayWrapper::ImGuiDemo() {
  if (imgui_demo_active_)
    ImGui::ShowDemoWindow(&imgui_demo_active_);
}

