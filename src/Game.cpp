#include "Game.hpp"
#include "GameState.hpp"
#include <memory>

Game::Game(bool *game_ctrl, bool run_at_least_once) {
  game_running_ptr_ = &game_running_;
  if (game_ctrl) {
    game_running_ptr_ = game_ctrl;
  }
  run_at_least_once_ = run_at_least_once;
  gui_ptr_ = std::make_unique<RayWrapper>();
  game_state_ptr_ = std::make_unique<GameState>();
  game_page_backup_ = GamePageFlags_Debug;
  Loop();
}

Game::~Game() {}

void Game::Loop() {
  game_running_ = *game_running_ptr_ || run_at_least_once_;
  while (game_running_) {
    if (!setup_ran_) {
      Setup();
    }
    HandleGameState();
    HandleGui();
    game_running_ = *game_running_ptr_ && game_running_;
  }
}

void Game::Setup() {
  if (!game_state_ptr_ || !gui_ptr_)
    return;

  gui_ptr_->Setup(game_state_ptr_);
  setup_ran_ = true;
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
    if (gui_ptr_) gui_ptr_->Setup(game_state_ptr_);
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
    gui_ptr_->Setup(game_state_ptr_);
  }
}
