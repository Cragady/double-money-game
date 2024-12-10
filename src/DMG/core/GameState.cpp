#include "DMG/core/GameState.hpp"

#include <raylib.h>

void GameState::Update() {
  delta_time_ = GetFrameTime();
  total_elapsed_time_ = GetTime();
  fps_ = GetFPS();
}

void GameState::ManageGamePageFlag(GamePageFlags flag, bool should_be_active) {
  if (should_be_active) {
    current_page_ |= flag;
  } else {
    current_page_ &= ~flag;
  }
};

bool GameState::GetGamePageFlag(GamePageFlags flag) {
  bool is_active = (current_page_ | flag) == current_page_;
  return is_active;
};

int GameState::GetTotalButtonClicks() {
  return multiply_chance_.total_hits_ + get_chance_.total_hits_ + add_chance_.total_hits_;
}
