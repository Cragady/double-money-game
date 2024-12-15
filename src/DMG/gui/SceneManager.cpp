#include "DMG/gui/SceneManager.hpp"

#include <memory>

#include "DMG/core/GameState.hpp"
#include "DMG/gui/DebugWindow.hpp"
#include "DMG/gui/Scene.hpp"
#include "DMG/raygui/MainCamera.hpp"

SceneManager::SceneManager() {
  default_camera_ = std::make_shared<MainCamera>();
  debug_window_ = std::make_shared<DebugWindow>();
}

SceneManager::~SceneManager() {};

void SceneManager::Setup(const GameStateUPtr &state, bool gui_loaded) {
  if (!current_scene_) return;
  current_scene_->Setup(state, gui_loaded);
}

void SceneManager::Update(const GameStateUPtr &state) {
  if (!current_scene_) return;
  current_scene_->Update(state);
};
void SceneManager::Shutdown(const GameStateUPtr &state) {
  if (!current_scene_) return;
  current_scene_->Shutdown(state);
};

bool SceneManager::CheckCurrentPage(const GameStateUPtr &state) {
  return state->GetGamePageFlag(_page_);
}
