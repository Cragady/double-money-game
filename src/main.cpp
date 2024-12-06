#include <iostream>
#include <terminal-colors.h>

#include "Game.hpp"
#include "RandomChance/RandomChance.hpp"

void SanityPrint();

int main(int argc, char **argv) {
  // SanityPrint();
  Game game;
  return 0;
}

void SanityPrint() {
  const char *msg = TERM_RED "Hello!" TERM_CRESET;
  std::cout << msg << std::endl;
  RandomChance doubleChance = RandomChance(1, 10000, 5000);
  doubleChance.TestRandom();
}

