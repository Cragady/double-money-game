#ifndef DMG_CORE_UTIL_COLOR_CONVERSION_HPP_
#define DMG_CORE_UTIL_COLOR_CONVERSION_HPP_

struct Rgb {
  double r; // a fraction between 0 and 1
  double g; // a fraction between 0 and 1
  double b; // a fraction between 0 and 1
};

struct Hsv {
  double h; // angle in degrees
  double s; // a fraction between 0 and 1
  double v; // a fraction between 0 and 1
};

Hsv rgb2hsv(Rgb in);
Rgb hsv2rgb(Hsv in);

#endif
