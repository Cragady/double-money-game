#include "DMG/core/RandomChance.hpp"

#include <common.h>
#include <raylib.h>
#include <terminal-colors.h>

#include <chrono>
#include <cstring>
#include <iostream>

RandomChance::RandomChance(int min, int max, int chance) {
  ReSeed();
  min_ = min;
  max_ = max;
  _chance_ = chance;
}

RandomChance::~RandomChance() {}

void RandomChance::SetNewChance(float new_chance) {
  if (new_chance > 1.0f) {
    new_chance = 1.0f;
  }
  if (new_chance < 0.0f) {
    new_chance = 0.0f;
  }
  _chance_ = new_chance * max_;
}

void RandomChance::ReSeed() {
  using namespace std::chrono;
  milliseconds ms =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());

  _seed_ = ms.count();
  SetRandomSeed(_seed_);
}

bool RandomChance::TakeChance() {
  int rolled_amount = GetRandomValue(min_, max_);
  return rolled_amount <= _chance_;
}

int RandomChance::GetRandom() {
  int rolled_amount = GetRandomValue(min_, max_);
  return rolled_amount;
}

void RandomChance::TestRandom() {
  std::cout << _seed_ << std::endl;

  for (int i = 0; i < 10; i++) {
    char status[BYTE_16] = TERM_RED "Failed";
    bool passed = TakeChance();
    if (passed) strncpy(status, TERM_GRN "Passed", BYTE_16);
    std::cout << "This attempt has: " << status << TERM_CRESET << std::endl;
  }
}
