#include <iostream>
#include <raylib.h>

#include "DMG/core/input/KeyboardInput.hpp"

bool KeyboardInput::EscapeSequence() {
  bool control_pressed =
      IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
  bool w_pressed = IsKeyDown(KEY_W);
  return control_pressed && w_pressed;
}

void KeyboardInput::TestLogKeys() {
  // int escape_sequence = (KEY_LEFT_CONTROL ^ KEY_RIGHT_CONTROL) | KEY_W;
  // if (IsKeyDown(KEY_LEFT_CONTROL)) {}
  std::cout << "--" << std::endl;
  int key = GetKeyPressed();
  while (key != 0) {
    std::cout << "Key is: " << key << std::endl;
    key = GetKeyPressed();
  }
  int uni = GetCharPressed();
  while (uni != 0) {
    std::cout << "uni is: " << uni << std::endl;
    uni = GetCharPressed();
  }
  std::cout << "--" << std::endl;
}
