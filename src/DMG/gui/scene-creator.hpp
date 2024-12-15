#ifndef DMG_GUI_SCENE_CREATOR_HPP_
#define DMG_GUI_SCENE_CREATOR_HPP_

#include <functional>
#include <memory>

#include "DMG/core/GameState.hpp"
#include "DMG/core/IGui.hpp"

class RayWrapper;
class DebugWindow;
class Scene;
class MainCamera;
using DebugWindowSPtr = std::shared_ptr<DebugWindow>;
using SceneSPtr = std::shared_ptr<Scene>;
using MainCameraSPtr = std::shared_ptr<MainCamera>;

namespace scenecreator {

class SceneCreator {
 public:
  SceneCreator(MainCameraSPtr = nullptr, DebugWindowSPtr = nullptr);

  SceneSPtr Setup(const GameStateUPtr &);
  void CreateCommonElements(const GameStateUPtr &, unsigned long *);
  void CreateDebugScene(const GameStateUPtr &);
  void AddWindowToCollections(IGuiSPtr, bool = true);
  void AddAndCreate(std::function<void()> &, unsigned long *, bool = false);

  DebugWindowSPtr debug_window_ = nullptr;
  MainCameraSPtr scene_camera_ = nullptr;
  SceneSPtr created_scene_ = nullptr;
  bool gui_setup_ = false;
};

} // namespace scenecreator

#endif
