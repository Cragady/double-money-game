#include "DMG/raygui/RayButton.hpp"

#include <raylib.h>
#include <rlgl.h>
#include <terminal-colors.h>

#include <iostream>

#include "DMG/core/util/color-conversion.hpp"

RayButton::RayButton() {}

RayButton::RayButton(char *fs_name, char *vs_name, std::string shader_path) {
  fs_file_name_ = fs_name;
  vs_file_name_ = vs_name;
  shader_path_ = shader_path;
}

void RayButton::GuiSetup() {
  const char *vertex_shader =
      TextFormat("%s%s", shader_path_.c_str(), vs_file_name_.c_str());
  const char *fragment_shader =
      TextFormat("%s%s", shader_path_.c_str(), fs_file_name_.c_str());
  shader_ = LoadShader(0, fragment_shader);
};
void RayButton::DataSetup(const GameStateUPtr &state) {};
void RayButton::Shutdown() { UnloadShader(shader_); };
void RayButton::Update(const GameStateUPtr &state) {
  button_pressed_ = false;
  color_shifting_.ShiftColor(state->delta_time_);

  Hsv color_to_convert = Hsv {
      .h = color_shifting_.colors_[0],
      .s = 1,
      .v = 1,
  };

  if (CheckCollisionPointRec(GetMousePosition(), rect_)) {
    color_to_convert.s = 0.5f;
    color_to_convert.v = 0.5f;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      button_pressed_ = true;
      if (ClickEvent) {
        ClickEvent(state);
      } else {
        std::cout << TERM_YEL
            "Click Event not assigned! Assign it via constructor or "
            "post ctor!" TERM_CRESET
                  << std::endl;
      }
    }
  }

  Rgb color_h = hsv2rgb(color_to_convert);
  render_color_[0] = (float)color_h.r;
  render_color_[1] = (float)color_h.g;
  render_color_[2] = (float)color_h.b;
};
void RayButton::BeginRender(const GameStateUPtr &state) {
  if (!open_) return;

  BeginShaderMode(shader_);
  int color_loc = GetShaderLocation(shader_, "u_fragmentColor");

  SetShaderValue(shader_, color_loc, &render_color_[0], RL_SHADER_UNIFORM_VEC3);
};
void RayButton::Render(const GameStateUPtr &state) {
  if (!open_) return;

  DrawRectangleRec(rect_, WHITE);
  // DrawTexture(texture_2d_, 0, 0, WHITE);
};
void RayButton::EndRender(const GameStateUPtr &state) {
  if (!open_) return;
  EndShaderMode();
};
void RayButton::FullRender(const GameStateUPtr &state) {
  BeginRender(state);
  Render(state);
  EndRender(state);
};

void RayButton::DefaultEvent(const GameStateUPtr &) {
  std::cout << "Click Event!!!" << std::endl;
}
