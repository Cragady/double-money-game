#include "DMG/raygui/RayButton.hpp"

#include <raylib.h>
#include <rlgl.h>
#include <terminal-colors.h>

#include <iostream>

#include "DMG/core/GameState.hpp"
#include "DMG/core/util/color-conversion.hpp"

RayButton::RayButton() { name_ = "Test Button"; }

RayButton::RayButton(char *fs_name, char *vs_name, std::string shader_path) {
  name_ = "Test Button";
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
  font_ = GetFontDefault();
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
  RenderText(state);
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

void RayButton::RenderText(const GameStateUPtr &state) {
  EndShaderMode();
  int test_font_size = 16;
  const char *name = name_.c_str();
  float font_spacing = 2.0f;
  Vector2 text_size = MeasureTextEx(font_, name, test_font_size, font_spacing);
  bool resize_rect = false;
  if (text_size.x > rect_.width) {
    rect_.width = text_size.x + 16;
    resize_rect = true;
  }
  if (text_size.y > rect_.height) {
    rect_.height = text_size.y + 16;
    resize_rect = true;
  }
  if (resize_rect) {
    BeginShaderMode(shader_);
    DrawRectangleRec(rect_, WHITE);
    EndShaderMode();
  }

  Vector2 text_pos = {
      .x = (rect_.width / 2 + rect_.x) - text_size.x / 2,
      .y = (rect_.height / 2 + rect_.y) - text_size.y / 2,
  };

  DrawTextEx(font_, name, text_pos, test_font_size, font_spacing, WHITE);
};

void RayButton::DefaultEvent(const GameStateUPtr &) {
  std::cout << "Click Event!!!" << std::endl;
}
