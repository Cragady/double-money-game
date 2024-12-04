#include <raylib.h>
#include <raymath.h>

#include "imgui.h"
#include "rlImGui.h"
#include "SceneViewWindow.hpp"

void SceneViewWindow::Setup() {
  ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

  Camera.fovy = 45;
  Camera.up.y = 1;
  Camera.position.y = 3;
  Camera.position.z = -25;

  Image img = GenImageChecked(256, 256, 32, 32, DARKGRAY, WHITE);
  GridTexture = LoadTextureFromImage(img);
  UnloadImage(img);
  GenTextureMipmaps(&GridTexture);
  SetTextureFilter(GridTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
  SetTextureWrap(GridTexture, TEXTURE_WRAP_CLAMP);
}

void SceneViewWindow::Shutdown() {
  UnloadRenderTexture(ViewTexture);
  UnloadTexture(GridTexture);
}

void SceneViewWindow::Show() {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::SetNextWindowSizeConstraints(
      ImVec2(400, 400),
      ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

  if (ImGui::Begin("3D View", &Open, ImGuiWindowFlags_NoScrollbar)) {
    Focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
    // draw the view
    rlImGuiImageRenderTextureFit(&ViewTexture, true);
  }
  ImGui::End();
  ImGui::PopStyleVar();
}

void SceneViewWindow::Update() {
  if (!Open)
    return;

  if (IsWindowResized()) {
    UnloadRenderTexture(ViewTexture);
    ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
  }

  float period = 10;
  float magnitude = 25;

  Camera.position.x = (float)(sinf((float)GetTime() / period) * magnitude);

  BeginTextureMode(ViewTexture);
  ClearBackground(SKYBLUE);

  BeginMode3D(Camera);

  // grid of cube trees on a plane to make a "world"
  DrawPlane(Vector3{0, 0, 0}, Vector2{50, 50}, BEIGE); // simple world plane
  float spacing = 4;
  int count = 5;

  for (float x = -count * spacing; x <= count * spacing; x += spacing) {
    for (float z = -count * spacing; z <= count * spacing; z += spacing) {
      Vector3 pos = {x, 0.5f, z};

      Vector3 min = {x - 0.5f, 0, z - 0.5f};
      Vector3 max = {x + 0.5f, 1, z + 0.5f};

      DrawCube(Vector3{x, 1.5f, z}, 1, 1, 1, GREEN);
      DrawCube(Vector3{x, 0.5f, z}, 0.25f, 1, 0.25f, BROWN);
    }
  }

  EndMode3D();
  EndTextureMode();
}
