#include "DMG/gui/Scene.hpp"

#include "DMG/gui/MainCamera.hpp"

Scene::Scene(MainCameraSPtr main_camera, DebugWindowSPtr debug_window) {
  // TODO: implement a configuration for a camera for a scene if needed
  scene_camera_ = main_camera;
  // TODO: implement a configuration for a debug window for a scene if needed
  debug_window_ = debug_window;
}

Scene::~Scene() {}

void Scene::Setup(const GameStateUPtr &state, bool gui_setup) {
  if (!scene_camera_) return;
  if (!gui_setup) scene_camera_->GuiSetup(state);
  scene_camera_->DataSetup(state);
}
void Scene::Update(const GameStateUPtr &state) {
  if (!scene_camera_) return;
  scene_camera_->Update(state);
  scene_camera_->FullRender(state);
}
void Scene::Shutdown(const GameStateUPtr &state) {
  if (!scene_camera_) return;
  scene_camera_->Shutdown(state);
}

void Scene::PassScenesToCamera() {
  if (!scene_camera_ || gui_passed_to_camera_) return;
  scene_camera_->guis_ = guis_;
  gui_passed_to_camera_ = true;
}
