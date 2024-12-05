#ifndef GAME_HPP
#define GAME_HPP

#include "RayWrapper.hpp"

class Game {
public:
  Game();
  ~Game();
  // Copy deletions
  Game (const Game &) = delete;
  Game &operator = (Game &) = delete;
  // Move deletions
  Game (Game &&) = delete;
  Game &operator = (Game &&) = delete;
  void Loop();

  RayWrapper gui;
  bool game_running_ = true;
};

#endif
