#include <cstring>
#include <iostream>
#include <terminal-colors.h>
#include <raylib.h>

#include "main.hpp"
#include "Demo.hpp"
#include "RandomChance/RandomChance.hpp"

int main(int argc, char **argv) {
  SanityPrint();
  SanityWindow();
  return 0;
}

void SanityPrint() {
  const char *msg = TERM_RED "Hello!" TERM_CRESET;
  std::cout << msg << std::endl;
  RandomChance doubleChance = RandomChance(1, 10000, 5000);
  doubleChance.TestRandom();
}

void SanityWindow() {
  Demo demo;
  demo.Prepare();

  while (!WindowShouldClose() && !demo.Quit) {
    demo.Update();
  }

  demo.Shutdown();
}
