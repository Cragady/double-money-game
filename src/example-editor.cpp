/*******************************************************************************************
 *
 *   raylib-extras [ImGui] example - editor
 *
 *	This is a more complex ImGui Integration
 *	It shows how to build windows on top of 2d and 3d views using a render
 *texture
 *
 *   Copyright (c) 2021 Jeffery Myers
 *
 ********************************************************************************************/

#include "RaylibStarter/ImageViewerWindow.hpp"
#include "RaylibStarter/SceneViewWindow.hpp"
#include "raylib.h"

#include "imgui.h"
#include "rlImGui.h"

void DoMainMenu();

bool Quit = false;

bool ImGuiDemoOpen = false;

ImageViewerWindow ImageViewer;
SceneViewWindow SceneView;


int main(int argc, char *argv[]) {
  // Initialization
  //--------------------------------------------------------------------------------------
  int screenWidth = 1900;
  int screenHeight = 900;

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight,
             "raylib-Extras [ImGui] example - ImGui Demo");
  SetTargetFPS(144);
  rlImGuiSetup(true);
  ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

  ImageViewer.Setup();
  ImageViewer.Open = true;

  SceneView.Setup();
  SceneView.Open = true;

  // Main game loop
  while (!WindowShouldClose() && !Quit) // Detect window close button or ESC key
  {
    ImageViewer.Update();
    SceneView.Update();

    BeginDrawing();
    ClearBackground(DARKGRAY);

    rlImGuiBegin();
    DoMainMenu();

    if (ImGuiDemoOpen)
      ImGui::ShowDemoWindow(&ImGuiDemoOpen);

    if (ImageViewer.Open)
      ImageViewer.Show();

    if (SceneView.Open)
      SceneView.Show();

    rlImGuiEnd();

    EndDrawing();
    //----------------------------------------------------------------------------------
  }
  rlImGuiShutdown();

  ImageViewer.Shutdown();
  SceneView.Shutdown();

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

void DoMainMenu() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit"))
        Quit = true;

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window")) {
      ImGui::MenuItem("ImGui Demo", nullptr, &ImGuiDemoOpen);
      ImGui::MenuItem("Image Viewer", nullptr, &ImageViewer.Open);
      ImGui::MenuItem("3D View", nullptr, &SceneView.Open);

      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
