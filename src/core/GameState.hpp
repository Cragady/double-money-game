#ifndef DMG_CORE_GAME_STATE_HPP_
#define DMG_CORE_GAME_STATE_HPP_

#include "RandomTracker.hpp"
#include <memory>

enum GamePage {
  GamePage_Debug,
  GamePage_Title,
  GamePage_Options,
  GamePage_Game,
  GamePage_Pause,
};

class GameState {
public:

  float delta_time_ = 0.0f;
  double total_elapsed_time_ = 0.0f;
  int fps_ = 0;

  GamePage current_page_ = GamePage_Title;
  bool reset_game_state_ = false;
  long double current_money_ = 0;
  long double current_percentage_currency_ = 0;

  RandomTracker multiply_chance_ = RandomTracker(RandomTrackerType_Multiply, 5000);
  RandomTracker get_chance_ = RandomTracker(RandomTrackerType_Get, 5000);
  RandomTracker add_chance_ = RandomTracker(RandomTrackerType_Add, 5000, true);

  void Update();
};

#endif
