#include "RandomTracker.hpp"

RandomTracker::RandomTracker(RandomTrackerType type, int chance_percentage,
                             bool first_guaranteed) {
  type_ = type;
  chance_percentage_ = chance_percentage;
  first_guaranteed_ = first_guaranteed;
};

void RandomTracker::SetNewChance(float new_chance) {
  random_engine_.SetNewChance(new_chance);
}

void RandomTracker::ResetRandomRange() {
  random_engine_.min_ = _roll_min_;
  random_engine_.max_ = _roll_max_;
}
