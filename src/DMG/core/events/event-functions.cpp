#include <terminal-colors.h>

#include <iostream>

#include "DMG/core/GameState.hpp"

namespace events {
void TestEvent() { std::cout << "This is a test event." << std::endl; }

void TestEvent(const GameStateUPtr &state) {
  std::cout << "This is a test event." << std::endl;
}

void TestRandom(const GameStateUPtr &) {
  const char *msg = TERM_RED "Hello!" TERM_CRESET;
  std::cout << msg << std::endl;
  RandomChance doubleChance = RandomChance(1, 10000, 5000);
  doubleChance.TestRandom();
};

void AddMoneyEvent(const GameStateUPtr &state) {
  // TODO: make actual implementation
  state->current_money_++;
}
} // namespace events
