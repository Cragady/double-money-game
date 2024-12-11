#ifndef DMG_CORE_UTIL_COLOR_SHIFTING_HPP_
#define DMG_CORE_UTIL_COLOR_SHIFTING_HPP_

// HSV
enum ColorShiftingDirection_ {
  ColorShiftingDirection_Up,
  ColorShiftingDirection_Down,
};

using ColorShiftingDirection = int;

struct ColorShiftingVals {
  int width = 3;
  float *val;
};

class ColorShifting {
 private:
  const float _COLOR_MAX_ = 360.0f;
  const float _COLOR_LOWEST_ = 0.0f;
  const float _COLOR_DIVISOR_[3] = {_COLOR_MAX_, _COLOR_MAX_, _COLOR_MAX_};
  const int _COLORS_LEN_ = 3;
  int _current_index_;
  int _next_index_;

 public:
  ColorShifting();
  ColorShifting(float t_color_high, float t_color_low, float t_speed);
  ~ColorShifting();
  // ColorShifting(ColorShifting const &other);
  ColorShifting(ColorShifting &other);
  // ColorShifting& operator=(ColorShifting &other);
  ColorShifting &operator=(ColorShifting other);

  ColorShifting(ColorShifting &&other);

  ColorShiftingVals ShiftColor(float delta_time);

  float colors_[3];
  ColorShiftingDirection direction_ = ColorShiftingDirection_Up;
  float color_high_;
  float color_low_;
  float shift_speed_;
  friend void swap(ColorShifting &first, ColorShifting &other);
};

void swap(ColorShifting &first, ColorShifting &other);

#endif
