#ifndef DMG_GAME_HPP_
#define DMG_GAME_HPP_

#include <memory>

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
  void HandleGui();

  std::unique_ptr<RayWrapper> gui_ptr = nullptr;
  bool game_running_ = true;
};

#endif
