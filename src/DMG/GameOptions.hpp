#ifndef DMG_GAME_OPTIONS_HPP_
#define DMG_GAME_OPTIONS_HPP_

#include <string>

typedef struct GameOptions {
  int width;
  int height;
  int fps;
  std::string name;
} GameOptions;

#endif