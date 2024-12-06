#ifndef DMG_CORE_RANDOM_CHANCE_HPP_
#define DMG_CORE_RANDOM_CHANCE_HPP_

class RandomChance {
public:
  RandomChance(int min = 1, int max = 10000, int chance = 5000);
  ~RandomChance();
  void SetNewChance(float new_chance = 0.5f);
  void ReSeed();
  bool TakeChance();
  void TestRandom();
private:
  unsigned long _seed_;
  int _chance_;
  int _max_;
  int _min_;
};

#endif
