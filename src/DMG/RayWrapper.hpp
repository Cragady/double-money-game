#ifndef DMG_RAY_WRAPPER_HPP_
#define DMG_RAY_WRAPPER_HPP_

#include "DMG/GameOptions.hpp"
#include "DMG/core/GameState.hpp"
#include "DMG/core/ICoreBase.hpp"
#include "DMG/core/input/KeyboardInput.hpp"
#include "DMG/gui/scene-creator.hpp"

namespace scenecreator {
class SceneCreator;
}

class Scene;
using SceneSPtr = std::shared_ptr<Scene>;
class MainCamera;
using MainCameraSPtr = std::shared_ptr<MainCamera>;
class DebugWindow;
using DebugWindowSPtr = std::shared_ptr<DebugWindow>;

class RayWrapper : public ICoreBase {
 public:
  RayWrapper(GameOptions game_options = GameOptions {
                 .width = 1200,
                 .height = 900,
                 .fps = 144,
                 .name = "Econ Wrecker: DMG"});
  ~RayWrapper();

  // ICoreBase
  void Setup(const GameStateUPtr &, bool = false) override;
  void Update(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;

  // RayWrapper
  void StartOfLoop();
  void EndOfLoop();
  void Loop(const GameStateUPtr &);
  void ImGuiDemo();

  int screen_width_;
  int screen_height_;
  int target_fps_;
  bool draw_fps_ = false;

  KeyboardInput key_input_;

  scenecreator::SceneCreator scene_creator_;
  SceneSPtr current_scene_ = nullptr;
  MainCameraSPtr default_camera_ = nullptr;
  DebugWindowSPtr debug_window_ = nullptr;
  bool hard_stop_ = false;
  bool glfw_ready_ = false;
  bool imgui_demo_active_ = false;
  bool reset_gui_ = false;
  bool gui_setup_ = false;

 private:
  GamePageFlags _page_ = GamePageFlags_Debug;
};

#endif
