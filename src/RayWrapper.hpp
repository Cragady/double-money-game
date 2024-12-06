#ifndef DMG_RAY_WRAPPER_HPP_
#define DMG_RAY_WRAPPER_HPP_

#include "KeyboardInput.hpp"
#include "../GameOptions.hpp"
#include "ButtonComponent.hpp"
#include "DebugWindow.hpp"

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
  void TesterApplication();

  int screen_width_;
  int screen_height_;
  int target_fps_;

  DebugWindow debug_window_;
  KeyboardInput key_input_;
  ButtonComponent button;

  bool hard_stop_ = false;
  bool glfw_ready_ = false;
  bool imgui_demo_active_ = false;
  bool tester_application_active_ = false;
  bool reset_gui_ = false;
};

#endif
