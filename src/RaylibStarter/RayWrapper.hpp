#ifndef RAY_WRAPPER_HPP
#define RAY_WRAPPER_HPP

#include "../Input/KeyboardInput.hpp"

class RayWrapper {
public:
  RayWrapper(int width = 800, int height = 450, int fps = 144);
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
