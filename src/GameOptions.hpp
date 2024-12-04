#ifndef GAME_OPTIONS_HPP
#define GAME_OPTIONS_HPP

#include <string>

typedef struct GameOptions {
  int width;
  int height;
  int fps;
  std::string name;
} GameOptions;

#endif
