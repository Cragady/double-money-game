#include "GameState.hpp"

#include <raylib.h>

void GameState::Update() {
  delta_time_ = GetFrameTime();
  total_elapsed_time_ = GetTime();
  fps_ = GetFPS();
}
