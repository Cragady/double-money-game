#ifndef DMG_GUI_SCENE_HPP_
#define DMG_GUI_SCENE_HPP_

#include "DMG/core/IGuiManager.hpp"

class MainCamera;
using MainCameraSPtr = std::shared_ptr<MainCamera>;
class DebugWindow;
using DebugWindowSPtr = std::shared_ptr<DebugWindow>;

class Scene : public IGuiManager {
 public:
  Scene(MainCameraSPtr, DebugWindowSPtr);
  ~Scene();

  void Setup(const GameStateUPtr &, bool) override;
  void Update(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;

  void PassScenesToCamera();

  // From IGuiManager
  // std::vector<IGuiSPtr> guis_;

  MainCameraSPtr scene_camera_ = nullptr;
  DebugWindowSPtr debug_window_ = nullptr;
  bool gui_passed_to_camera_ = false;
};

#endif
