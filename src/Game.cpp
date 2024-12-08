#include "Game.hpp"
#include "GameState.hpp"
#include <memory>

Game::Game() {
  gui_ptr_ = std::make_unique<RayWrapper>();
  game_state_ptr_ = std::make_unique<GameState>();
  game_page_backup_ = GamePageFlags_Debug;
  Loop();
}

Game::~Game() {}

void Game::Loop() {
  while (game_running_) {
    HandleGameState();
    HandleGui();
  }
}

void Game::HandleGameState() {
  if (!game_state_ptr_)
    return;

  game_state_ptr_->Update();

  if (game_state_ptr_->reset_game_state_) {
    game_page_backup_ = game_state_ptr_->current_page_;

    game_state_ptr_.reset();

    game_state_ptr_ = std::make_unique<GameState>();
    game_state_ptr_->current_page_ = game_page_backup_;
  }
}

void Game::HandleGui() {
  if (!gui_ptr_ || !game_state_ptr_)
    return;
  gui_ptr_->Loop(game_state_ptr_);
  game_running_ = !gui_ptr_->hard_stop_;
  if (gui_ptr_->reset_gui_) {
    gui_ptr_.reset();
    gui_ptr_ = std::make_unique<RayWrapper>();
    gui_ptr_->reset_gui_ = false;
  }
}
