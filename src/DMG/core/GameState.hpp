#ifndef DMG_CORE_GAME_STATE_HPP_
#define DMG_CORE_GAME_STATE_HPP_

#include <memory>

#include "DMG/core/RandomTracker.hpp"
#include "raylib.h"

// TODO: consider moving enum to diff file
enum GamePageFlags_ {
  GamePageFlags_None = 1 << 0,
  GamePageFlags_Debug = 1 << 1,
  GamePageFlags_Title = 1 << 2,
  GamePageFlags_Options = 1 << 3,
  GamePageFlags_Game = 1 << 4,
  GamePageFlags_Pause = 1 << 5,
};

using GamePageFlags = int;

class DebugWindow;
using CameraSPtr = std::shared_ptr<Camera>;
using DebugWindowWPtr = std::weak_ptr<DebugWindow>;

class GameState {
 public:
  void Update();
  void ManageGamePageFlag(GamePageFlags, bool);
  bool GetGamePageFlag(GamePageFlags);
  int GetTotalButtonClicks();

  // TODO: change below to react to compile time constant somewhere
  bool is_debug_active_ = true;
  float delta_time_ = 0.0f;
  double total_elapsed_time_ = 0.0f;
  int fps_ = 0;
  bool draw_fps_ = true;
  int screen_width_ = 0;
  int screen_height_ = 0;
  CameraSPtr main_camera_ = nullptr;
  DebugWindowWPtr debug_window_;

  Ray mouse_ray_ = {
      .position = {0, 0, 0},
      .direction = {0, 0, 0},
  };
  GamePageFlags current_page_ = GamePageFlags_Debug;
  bool hard_stop_ = false;
  bool reset_game_state_ = false;
  long double current_money_ = 0;
  long double current_percentage_currency_ = 0;

  RandomTracker multiply_chance_ =
      RandomTracker(RandomTrackerType_Multiply, 5000);
  RandomTracker get_chance_ = RandomTracker(RandomTrackerType_Get, 5000);
  RandomTracker add_chance_ = RandomTracker(RandomTrackerType_Add, 5000, true);
};

using GameStateUPtr = std::unique_ptr<GameState>;

#endif
