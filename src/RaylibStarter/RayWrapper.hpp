#ifndef RAY_WRAPPER_HPP
#define RAY_WRAPPER_HPP

#include "../Input/KeyboardInput.hpp"
#include "../GameOptions.hpp"
#include "ButtonComponent.hpp"
#include "../Window/DebugWindow.hpp"

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


  DebugWindow debug_window_;
  KeyboardInput key_input_;
  ButtonComponent button;
  bool game_running_;
  bool glfw_ready_;
  bool imgui_demo_active_;
  bool tester_application_active_;
  int screen_width_;
  int screen_height_;
  int target_fps_;
};

#endif
