#include "DMG/gui/SceneManager.hpp"

#include <memory>

#include "DMG/core/GameState.hpp"
#include "DMG/gui/MainCamera.hpp"
#include "DMG/gui/Scene.hpp"
#include "DMG/gui/imgui/DebugWindow.hpp"
#include "DMG/gui/scene-creator.hpp"

SceneManager::SceneManager() {
  default_camera_ = std::make_shared<MainCamera>();
  debug_window_ = std::make_shared<DebugWindow>();

  scene_creator_ = scenecreator::SceneCreator(default_camera_, debug_window_);

  debug_window_->CopyBoolPtrOne(
      Dw_CbpArgs {.name = "ImGui Demo", .bool_ptr = &imgui_demo_active_});
  debug_window_->SetProgramFlag(
      Dw_CbpArgs {.name = "Reset GUI", .bool_ptr = &reset_gui_});
}

SceneManager::~SceneManager() {};

void SceneManager::Setup(const GameStateUPtr &state, bool gui_loaded) {
  if (!current_scene_) current_scene_ = scene_creator_.Setup(state);
  if (!current_scene_) return;
  current_scene_->Setup(state, gui_loaded);
}

void SceneManager::Update(const GameStateUPtr &state) {
  if (!current_scene_) return;
  current_scene_->Update(state);
  ImGuiDemo();
};
void SceneManager::Shutdown(const GameStateUPtr &state) {
  if (!current_scene_) return;
  current_scene_->Shutdown(state);
};

void SceneManager::ImGuiDemo() {
  if (imgui_demo_active_) ImGui::ShowDemoWindow(&imgui_demo_active_);
}

bool SceneManager::CheckCurrentPage(const GameStateUPtr &state) {
  return state->GetGamePageFlag(_page_);
}
