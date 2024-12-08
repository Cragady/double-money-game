#include "GameState.hpp"
#include <iostream>

namespace events {
  void TestEvent() {
    std::cout << "This is a test event." << std::endl;
  }

  void TestEvent(const GameStateUPtr &state) {
    std::cout << "This is a test event." << std::endl;
  }

  void AddMoneyEvent(const GameStateUPtr &state) {
    // TODO: make actual implementation
    state->current_money_++;
  }
}
