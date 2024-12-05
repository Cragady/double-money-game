#include "Game.hpp"
#include <memory>

Game::Game() {
  gui_ptr = std::make_unique<RayWrapper>();
  Loop();
}

Game::~Game() {}

void Game::Loop() {
  while (game_running_) {
    HandleGui();
  }
}

void Game::HandleGui() {
  if (!gui_ptr) return;
  gui_ptr->Loop();
  game_running_ = !gui_ptr->hard_stop_;
  if (gui_ptr->reset_gui_) {
    gui_ptr.reset();
    gui_ptr = std::make_unique<RayWrapper>();
    gui_ptr->reset_gui_ = false;
  }
}
