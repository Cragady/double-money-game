#ifndef DMG_GAME_HPP_
#define DMG_GAME_HPP_

#include <memory>

#include "GameState.hpp"
#include "RayWrapper.hpp"

class Game {
public:
  Game();
  ~Game();
  // Copy deletions
  Game(const Game &) = delete;
  Game &operator=(Game &) = delete;
  // Move deletions
  Game(Game &&) = delete;
  Game &operator=(Game &&) = delete;
  void Loop();
  void HandleGameState();
  void HandleGui();

  std::unique_ptr<RayWrapper> gui_ptr_ = nullptr;
  std::shared_ptr<GameState> game_state_ptr_ = nullptr;
  GamePage game_page_backup_ = GamePage_Debug;
  bool game_running_ = true;
};

#endif
