#ifndef DMG_GUI_SCENE_MANAGER_HPP_
#define DMG_GUI_SCENE_MANAGER_HPP_

#include <memory>

#include "DMG/core/GameState.hpp"
#include "DMG/core/ICoreBase.hpp"

class Scene;
using SceneSPtr = std::shared_ptr<Scene>;
class MainCamera;
using MainCameraSPtr = std::shared_ptr<MainCamera>;
class DebugWindow;
using DebugWindowSPtr = std::shared_ptr<DebugWindow>;

class SceneManager : public ICoreBase {
 public:
  SceneManager();
  ~SceneManager();

  // ICoreBase
  void Setup(const GameStateUPtr &, bool) override;
  void Update(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;

  bool CheckCurrentPage(const GameStateUPtr &);

  SceneSPtr current_scene_ = nullptr;
  MainCameraSPtr default_camera_ = nullptr;
  DebugWindowSPtr debug_window_ = nullptr;

 private:
  GamePageFlags _page_ = GamePageFlags_Debug;
};

#endif
