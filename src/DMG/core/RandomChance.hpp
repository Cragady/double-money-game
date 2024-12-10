#ifndef DMG_CORE_RANDOM_CHANCE_HPP_
#define DMG_CORE_RANDOM_CHANCE_HPP_

#define RANDOM_CHANCE_ROLL_MIN_DEFAULT 1
#define RANDOM_CHANCE_ROLL_MAX_DEFAULT 10000
#define RANDOM_CHANCE_ROLL_DEFAULT_PERCENTAGE_AS_INT 5000
#define RANDOM_CHANCE_ROLL_DEFAULT_PERCENTAGE_AS_FLOAT 0.5f

class RandomChance {
 public:
  RandomChance(int min = RANDOM_CHANCE_ROLL_MIN_DEFAULT,
               int max = RANDOM_CHANCE_ROLL_MAX_DEFAULT,
               int chance = RANDOM_CHANCE_ROLL_DEFAULT_PERCENTAGE_AS_INT);
  ~RandomChance();
  void SetNewChance(
      float new_chance = RANDOM_CHANCE_ROLL_DEFAULT_PERCENTAGE_AS_FLOAT);
  void ReSeed();
  bool TakeChance();
  int GetRandom();
  void TestRandom();
  int max_;
  int min_;

 private:
  unsigned long _seed_;
  int _chance_;
};

#endif
