#ifndef DMG_RAY_WRAPPER_HPP_
#define DMG_RAY_WRAPPER_HPP_

#include "DMG/GameOptions.hpp"
#include "DMG/core/GameState.hpp"
#include "DMG/core/input/KeyboardInput.hpp"
#include "DMG/gui/PageCreator.hpp"
#include "DMG/gui/WindowManager.hpp"
#include "DMG/raygui/GuiManager.hpp"
#include "DMG/raygui/MainCamera.hpp"

class RayWrapper {
 public:
  RayWrapper(GameOptions game_options = GameOptions {
                 .width = 1200,
                 .height = 900,
                 .fps = 144,
                 .name = "Econ Wrecker: DMG"});
  ~RayWrapper();

  void StartOfLoop();
  void EndOfLoop();
  void Setup(const GameStateUPtr &);
  void Loop(const GameStateUPtr &);
  void Update(const GameStateUPtr &);
  void Shutdown(const GameStateUPtr &);
  void ImGuiDemo();

  int screen_width_;
  int screen_height_;
  int target_fps_;
  bool draw_fps_ = false;

  PageCreator page_creator_;
  WindowManagerSPtr window_manager_ = nullptr;
  GuiManagerSPtr gui_manager_ = nullptr;
  KeyboardInput key_input_;

  MainCamera camera_;
  bool hard_stop_ = false;
  bool glfw_ready_ = false;
  bool imgui_demo_active_ = false;
  bool reset_gui_ = false;
  bool gui_setup_ = false;
};

#endif
