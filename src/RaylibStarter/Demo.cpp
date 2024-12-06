#include <iostream>
#include <terminal-colors.h>

#include "Demo.hpp"
#include "imgui.h"
#include "rlImGui.h"
#include <raylib.h>

Demo::Demo() {
  Prepare();
  GameLoop();
}

Demo::~Demo() {
  Shutdown();
}

void Demo::Prepare() {

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight,
             "raylib-Extras [ImGui] example - ImGui Demo");
  SetTargetFPS(144);
  rlImGuiSetup(true);
  ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

  ImageViewer.Setup();
  ImageViewer.open_ = true;

  SceneView.Setup();
  SceneView.open_ = true;
}

void Demo::Update() {
  ImageViewer.Update();
  SceneView.Update();

  BeginDrawing();
  ClearBackground(DARKGRAY);

  rlImGuiBegin();
  DoMainMenu();

  if (ImGuiDemoOpen)
    ImGui::ShowDemoWindow(&ImGuiDemoOpen);

  if (ImageViewer.open_)
    ImageViewer.FullRender();

  if (SceneView.open_)
    SceneView.FullRender();

  rlImGuiEnd();

  EndDrawing();
}

void Demo::Shutdown() {
  std::cout << TERM_RED "Shutting Down" TERM_CRESET << std::endl;

  rlImGuiShutdown();

  ImageViewer.Shutdown();
  SceneView.Shutdown();

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
}

void Demo::DoMainMenu() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit"))
        Quit = true;

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window")) {
      ImGui::MenuItem("ImGui Demo", nullptr, &ImGuiDemoOpen);
      ImGui::MenuItem("Image Viewer", nullptr, &ImageViewer.open_);
      ImGui::MenuItem("3D View", nullptr, &SceneView.open_);

      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}

void Demo::GameLoop() {
  while (!WindowShouldClose() && !Quit) {
    Update();
  }
};
