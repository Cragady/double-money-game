#ifndef DMG_CORE_RANDOM_TRACKER_HPP_
#define DMG_CORE_RANDOM_TRACKER_HPP_

#include "RandomChance.hpp"

enum RandomTrackerType {
  RandomTrackerType_None,
  RandomTrackerType_Multiply,
  RandomTrackerType_Get,
  RandomTrackerType_Add,
  RandomTrackerType_PassiveAdd,
};

class RandomTracker {
public:
  RandomTracker(RandomTrackerType type = RandomTrackerType_None,
                int chance_percentage = RANDOM_CHANCE_ROLL_DEFAULT_PERCENTAGE_AS_INT,
                bool first_guaranteed = false);

  RandomChance random_engine_ = RandomChance(
      RANDOM_CHANCE_ROLL_MIN_DEFAULT, RANDOM_CHANCE_ROLL_MAX_DEFAULT,
      RANDOM_CHANCE_ROLL_DEFAULT_PERCENTAGE_AS_INT);
  RandomTrackerType type_ = RandomTrackerType_None;
  int current_hits_ = 0;
  int max_hits_ = 0;
  int chance_percentage_ = RANDOM_CHANCE_ROLL_DEFAULT_PERCENTAGE_AS_INT;
  int low_percentage_;
  int high_percentage_;
  bool first_guaranteed_ = false;
  float health_ = 1.0f;
  float damage_to_receive_ = 1.0f;
  int low_roll_;
  int high_roll_;

  void SetNewChance(float = RANDOM_CHANCE_ROLL_DEFAULT_PERCENTAGE_AS_FLOAT);
  void ResetRandomRange();

private:
  int _roll_min_ = RANDOM_CHANCE_ROLL_MIN_DEFAULT;
  int _roll_max_ = RANDOM_CHANCE_ROLL_MAX_DEFAULT;
};

#undef DEFAULT_PERCENTAGE
#endif
