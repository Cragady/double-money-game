#ifndef RANDOM_CHANCE_HPP
#define RANDOM_CHANCE_HPP

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
