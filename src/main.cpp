#include <iostream>
#include <terminal-colors.h>

#include "RandomChance/RandomChance.hpp"
#include "RayWrapper.hpp"
#include "main.hpp"

int main(int argc, char **argv) {
  // SanityPrint();
  RayWrapper game;
  return 0;
}

void SanityPrint() {
  const char *msg = TERM_RED "Hello!" TERM_CRESET;
  std::cout << msg << std::endl;
  RandomChance doubleChance = RandomChance(1, 10000, 5000);
  doubleChance.TestRandom();
}

