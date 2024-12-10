#ifndef DMG_GAME_HPP_
#define DMG_GAME_HPP_

#include <memory>

#include "DMG/RayWrapper.hpp"
#include "DMG/core/GameState.hpp"

class Game {
 public:
  Game(bool *game_ctrl = nullptr, bool run_at_least_once = false);
  ~Game();
  // Copy deletions
  Game(const Game &) = delete;
  Game &operator=(Game &) = delete;
  // Move deletions
  Game(Game &&) = delete;
  Game &operator=(Game &&) = delete;
  void Setup();
  void Loop();
  void HandleGameState();
  void HandleGui();

  std::unique_ptr<RayWrapper> gui_ptr_ = nullptr;
  GameStateUPtr game_state_ptr_ = nullptr;
  GamePageFlags game_page_backup_ = GamePageFlags_Debug;
  bool *game_running_ptr_ = nullptr;
  bool game_running_ = true;
  bool setup_ran_ = false;
  bool run_at_least_once_ = false;
};

#endif
