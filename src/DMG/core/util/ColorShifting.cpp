#include "DMG/core/util/ColorShifting.hpp"

#include <utility>

// HSV
ColorShifting::ColorShifting() {
  shift_speed_ = 10.0f;
  color_high_ = _COLOR_MAX_;
  color_low_ = _COLOR_LOWEST_;
  colors_[0] = color_low_;
  colors_[1] = color_high_;
  colors_[2] = color_high_;
  _current_index_ = 0;
  _next_index_ = _COLORS_LEN_ - 1;
}

ColorShifting::ColorShifting(float t_color_high, float t_color_low,
                             float t_speed) {
  shift_speed_ = t_speed;
  color_high_ = t_color_high <= _COLOR_MAX_ ? t_color_high : _COLOR_MAX_;
  color_low_ = t_color_low >= _COLOR_LOWEST_ ? t_color_low : _COLOR_LOWEST_;

  if (color_low_ >= color_high_) color_low_ = _COLOR_LOWEST_;
  if (color_high_ <= color_low_) color_high_ = _COLOR_MAX_;

  colors_[0] = color_low_;
  colors_[1] = color_high_;
  colors_[2] = color_high_;
  _current_index_ = 0;
  _next_index_ = _COLORS_LEN_ - 1;
}

ColorShifting::~ColorShifting() {};

ColorShifting::ColorShifting(ColorShifting &other)
    : ColorShifting(other.color_high_, other.color_low_, other.shift_speed_) {}

ColorShifting::ColorShifting(ColorShifting &&other)
    : ColorShifting(other.color_high_, other.color_low_, other.shift_speed_) {}

// ColorShifting &ColorShifting::operator=(ColorShifting &other) {
//   swap(*this, other);
//   return *this;
// };

ColorShifting &ColorShifting::operator=(ColorShifting other) {
  swap(*this, other);
  return *this;
};

void swap(ColorShifting &first, ColorShifting &second) {
  using std::swap;
  swap(first.shift_speed_, second.shift_speed_);
  swap(first.color_high_, second.color_high_);
  swap(first.color_low_, second.color_low_);
  swap(first.colors_, second.colors_);
  swap(first._current_index_, second._current_index_);
  swap(first._next_index_, second._next_index_);
}

ColorShiftingVals ColorShifting::ShiftColor(float delta_time) {
  float delta_color = shift_speed_ * delta_time;

  float *current_color_control = &colors_[_current_index_];
  // float *next_color_control = &colors_[_next_index_];

  if (direction_ == ColorShiftingDirection_Up) {
    *current_color_control += delta_color;
  } else {
    *current_color_control -= delta_color;
  }

  if (*current_color_control <= color_low_) {
    *current_color_control = color_high_;
  }
  if (*current_color_control >= color_high_) {
    *current_color_control = color_low_;
  }

  float colors_value[3] = {colors_[0] / _COLOR_DIVISOR_[0],
                           colors_[1] / _COLOR_DIVISOR_[1],
                           colors_[2] / _COLOR_DIVISOR_[2]};

  return ColorShiftingVals {
      .val = colors_value,
  };
}
