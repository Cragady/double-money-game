#ifndef DMG_RAY_WRAPPER_HPP_
#define DMG_RAY_WRAPPER_HPP_

#include "GameState.hpp"
#include "KeyboardInput.hpp"
#include "GameOptions.hpp"
#include "PageCreator.hpp"
#include "WindowManager.hpp"

class RayWrapper {
public:
  RayWrapper(GameOptions game_options = GameOptions {
    .width = 1200,
    .height = 900,
    .fps = 144,
    .name = "Econ Wrecker: DMG"
  });
  ~RayWrapper();

  void StartOfLoop();
  void EndOfLoop();
  void Setup(const GameStateUPtr &);
  void Loop(const GameStateUPtr &);
  void Update(const GameStateUPtr &);
  void ImGuiDemo();

  int screen_width_;
  int screen_height_;
  int target_fps_;

  PageCreator page_creator_;
  WindowManagerSPtr window_manager_ = nullptr;
  KeyboardInput key_input_;

  bool hard_stop_ = false;
  bool glfw_ready_ = false;
  bool imgui_demo_active_ = false;
  bool reset_gui_ = false;
  bool gui_setup_ = false;
};

#endif
