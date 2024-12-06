#include <terminal-colors.h>

#include "RlImGuiDemo.hpp"
#include "imgui.h"
#include <raylib.h>

RlImGuiDemo::RlImGuiDemo() {
  Prepare();
}

RlImGuiDemo::~RlImGuiDemo() {}

void RlImGuiDemo::Prepare() {

  image_viewer_.Setup();
  image_viewer_.open_ = true;

  scene_view_.Setup();
  scene_view_.open_ = true;
}

void RlImGuiDemo::Update() {
  image_viewer_.Update();
  scene_view_.Update();
}

void RlImGuiDemo::Render() {
  DoMainMenu();

  if (imgui_demo_open_)
    ImGui::ShowDemoWindow(&imgui_demo_open_);

  if (image_viewer_.open_)
    image_viewer_.FullRender();

  if (scene_view_.open_)
    scene_view_.FullRender();
}

void RlImGuiDemo::DoMainMenu() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit"))
        quit_ = true;

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window")) {
      ImGui::MenuItem("ImGui Demo", nullptr, &imgui_demo_open_);
      ImGui::MenuItem("Image Viewer", nullptr, &image_viewer_.open_);
      ImGui::MenuItem("3D View", nullptr, &scene_view_.open_);

      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
