#ifndef DMG_RAY_WRAPPER_HPP_
#define DMG_RAY_WRAPPER_HPP_

#include "KeyboardInput.hpp"
#include "GameOptions.hpp"
#include "Button.hpp"
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
  void Loop();
  void Update();
  void ImGuiDemo();

  int screen_width_;
  int screen_height_;
  int target_fps_;

  WindowManager window_manager_;
  KeyboardInput key_input_;
  Button button;

  bool hard_stop_ = false;
  bool glfw_ready_ = false;
  bool imgui_demo_active_ = false;
  bool reset_gui_ = false;
};

#endif
