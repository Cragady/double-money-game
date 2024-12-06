#include <iostream>

#include <raylib.h>
#include <raymath.h>
#include <terminal-colors.h>
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "events/event-functions.hpp"
#include "RayWrapper.hpp"
#include "imgui.h"
#include "rlImGui.h"

RayWrapper::RayWrapper(GameOptions game_options) {
  screen_width_ = game_options.width;
  screen_height_ = game_options.height;
  target_fps_ = game_options.fps;

  debug_window_.CopyBoolPtrs(
      Dw_CbpArgs{.name = "ImGui Demo", .bool_ptr = &imgui_demo_active_},
      Dw_CbpArgs{.name = "Tester Application",
                 .bool_ptr = &tester_application_active_});
  debug_window_.SetProgramFlag(
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

  button.ClickEvent = events::TestEvent;
  rlImGuiSetup(true);
  // NOTE: The below will disable movement from click/dragging on imgui window
  // ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
  SetExitKey(KEY_NULL);
  GLFWwindow *window = (GLFWwindow *)GetWindowHandle();
  // glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
  glfwSetWindowSize(window, screen_width_, screen_height_);
  Loop();
}

RayWrapper::~RayWrapper() {
  std::cout << TERM_RED "Shutting Down" TERM_CRESET << std::endl;
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
  // Update Portion
  button.Update();
  // Render Portion
  debug_window_.FullRender();
  ImGuiDemo();
  TesterApplication();
}

void RayWrapper::ImGuiDemo() {
  if (imgui_demo_active_)
    ImGui::ShowDemoWindow(&imgui_demo_active_);
}

void RayWrapper::TesterApplication() {
  // TODO: remove/replace for actual implementation
  if (!tester_application_active_)
    return;

  ImGui::Begin("My First Tool", &tester_application_active_,
               ImGuiWindowFlags_NoBackground);
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
      }
      if (ImGui::MenuItem("Close", "Ctrl+W")) {
        tester_application_active_ = false;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  // Edit a color stored as 4 floats
  float my_color[4] = {1.0f, 0.25f, 0.5f, 1.0f};
  ImGui::ColorEdit4("Color", my_color);

  // Generate samples and plot them
  float samples[100];
  for (int n = 0; n < 100; n++)
    samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
  ImGui::PlotLines("Samples", samples, 100);

  // Display contents in a scrolling region
  ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
  ImGui::BeginChild("Scrolling");
  for (int n = 0; n < 50; n++)
    ImGui::Text("%04d: Some text", n);
  ImGui::EndChild();
  ImGui::End();
}
