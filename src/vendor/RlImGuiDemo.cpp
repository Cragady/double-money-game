#include <terminal-colors.h>

#include "RlImGuiDemo.hpp"
#include "imgui.h"
#include <raylib.h>

RlImGuiDemo::RlImGuiDemo() { name_ = "RlImGui Demo Windows"; }

RlImGuiDemo::~RlImGuiDemo() {}

void RlImGuiDemo::GuiSetup() {};
void RlImGuiDemo::DataSetup(const GameStateUPtr &state) {};
void RlImGuiDemo::Setup(const GameStateUPtr &state) {
  image_viewer_.Setup(state);
  image_viewer_.open_ = true;
  scene_view_.Setup(state);
  scene_view_.open_ = true;
}

void RlImGuiDemo::Shutdown() {
  image_viewer_.Shutdown();
  scene_view_.Shutdown();
};

void RlImGuiDemo::Update(const GameStateUPtr &state) {
  image_viewer_.Update(state);
  scene_view_.Update(state);
}

void RlImGuiDemo::BeginRender(const GameStateUPtr &state) {};
void RlImGuiDemo::Render(const GameStateUPtr &state) {};
void RlImGuiDemo::EndRender(const GameStateUPtr &state) {};
void RlImGuiDemo::FullRender(const GameStateUPtr &state) {
  if (!open_)
    return;
  DoMainMenu();

  if (imgui_demo_open_)
    ImGui::ShowDemoWindow(&imgui_demo_open_);

  if (image_viewer_.open_)
    image_viewer_.FullRender(state);

  if (scene_view_.open_)
    scene_view_.FullRender(state);
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
