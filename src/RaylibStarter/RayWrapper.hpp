#ifndef RAY_WRAPPER_HPP
#define RAY_WRAPPER_HPP

#include "../Input/KeyboardInput.hpp"
#include "../GameOptions.hpp"

class RayWrapper {
public:
  RayWrapper(GameOptions game_options = GameOptions {
    .width = 1200,
    .height = 900,
    .fps = 144,
    .name = "Econ Wrecker"
  });
  ~RayWrapper();

  void StartOfLoop();
  void EndOfLoop();
  void Loop();
  void Update();
  void TesterApplication();


  KeyboardInput key_input_;
  bool game_running_;
  int screen_width_;
  int screen_height_;
  int target_fps_;
};

#endif
