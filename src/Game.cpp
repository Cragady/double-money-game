#include "Game.hpp"

Game::Game() {
  Loop();
}

Game::~Game() {}

void Game::Loop() {
  while (game_running_) {
    gui.Loop();
    game_running_ = !gui.hard_stop_;
  }
}
