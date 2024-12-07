#include <terminal-colors.h>

#include "RlImGuiDemo.hpp"
#include "imgui.h"
#include <raylib.h>

RlImGuiDemo::RlImGuiDemo() {}

RlImGuiDemo::~RlImGuiDemo() {}

void RlImGuiDemo::Setup() {
  image_viewer_.Setup();
  scene_view_.Setup();
}

void RlImGuiDemo::Shutdown() {
  image_viewer_.Shutdown();
  scene_view_.Shutdown();
};

void RlImGuiDemo::Update() {
  image_viewer_.Update();
  scene_view_.Update();
}


void RlImGuiDemo::BeginRender() {};
void RlImGuiDemo::Render() {};
void RlImGuiDemo::EndRender() {};
void RlImGuiDemo::FullRender() {
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
