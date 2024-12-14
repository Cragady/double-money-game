#include "DMG/raygui/RayButton.hpp"

#include <raylib.h>
#include <rlgl.h>
#include <terminal-colors.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "DMG/core/GameState.hpp"
#include "DMG/core/util/color-conversion.hpp"
#include "DMG/vendor/util/raylib-text-draw-3d.hpp"

RayButton::RayButton() { name_ = "Test Button"; }

RayButton::RayButton(char *fs_name, char *vs_name, std::string shader_path) {
  name_ = "Test Button";
  fs_file_name_ = fs_name;
  vs_file_name_ = vs_name;
  shader_path_ = shader_path;
}

void RayButton::GuiSetup(const GameStateUPtr &state) {
  // const char *vertex_shader =
  //     TextFormat("%s%s", shader_path_.c_str(), vs_file_name_.c_str());
  const char *fragment_shader =
      TextFormat("%s%s", shader_path_.c_str(), fs_file_name_.c_str());
  // shader_ = LoadShader(vertex_shader, fragment_shader);
  shader_ = LoadShader(0, fragment_shader);
  font_ = GetFontDefault();
};
void RayButton::DataSetup(const GameStateUPtr &state) {};
void RayButton::Shutdown(const GameStateUPtr &state) { UnloadShader(shader_); };
void RayButton::Update(const GameStateUPtr &state) {
  button_pressed_ = false;
  color_shifting_.ShiftColor(state->delta_time_);

  Hsv color_to_convert = Hsv {
      .h = color_shifting_.colors_[0],
      .s = 1,
      .v = 1,
  };

  RayCollision collision = GetRayCollisionBox(
      state->mouse_ray_,
      (BoundingBox) {
          (Vector3) {position_.x - size_.x / 2, position_.y - size_.y / 2,
                     position_.z - size_.z / 2},
          (Vector3) {position_.x + size_.x / 2, position_.y + size_.y / 2,
                     position_.z + size_.z / 2}});

  if (collision.hit) {
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

  DrawCubeV(position_, size_, WHITE);
  // DrawRectangleRec(rect_, WHITE);
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
  float font_spacing = 2.0f;
  float line_spacing = 1.2f;
  std::string display_text = name_;
  // std::string display_text = "Heeyooo ~~<3~~";
  // std::string display_text = "Heeyooo <3 asdfjdsakl aksdljfdsalk; lkasdjfkl
  // l;asdkf;j";
  Vector3 text_size = vutil::MeasureText3D(
      font_, display_text.c_str(), test_font_size, font_spacing, line_spacing);
  bool resize_cube = false;
  if (text_size.x > size_.x) {
    size_.x = text_size.x + 0.5f;
    resize_cube = true;
  }
  if (text_size.y > size_.y) {
    size_.y = text_size.y + 0.5f;
    resize_cube = true;
  }
  if (resize_cube) {
    BeginShaderMode(shader_);
    DrawCubeV(position_, size_, WHITE);
    EndShaderMode();
  }

  rlPushMatrix();
  const int ROTS = 3;
  float angles[ROTS] = {90.0f, 180.0f, 180.0f};
  glm::vec3 rotations[ROTS] {
      {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}};
  glm::mat4 rotation_matrix;

  glm::vec3 og_text_pos = glm::vec3(
      // .x = (rect_.width / 2 + rect_.x) - text_size.x / 2,
      // .y = (rect_.height / 2 + rect_.y) - text_size.y / 2,
      // (position_.x + size_.x / 2) - text_size.x / 2,
      // (position_.y + size_.y / 2) - text_size.y / 2,
      (position_.x) - text_size.x / 2,
      // We use .z here because the text is originally rotated!
      (position_.y) + text_size.z / 2, (position_.z + size_.z / 2) + 0.1);

  for (int i = 0; i < ROTS; i++) {
    glm::vec3 rotation = rotations[i];
    float angle = angles[i];
    // We only pay attention to the first rotation for `rlRotatef`, because we
    // are fixing the damage done by this rotation and "undoing" the y and z
    // rotations
    if (i == 0) rlRotatef(angle, rotation.x, rotation.y, rotation.z);

    // Handling position w/rotation is a bit weird

    if (i == 0) rotation_matrix = glm::mat4(1.0);
    rotation_matrix =
        glm::rotate(rotation_matrix, glm::radians(angle), rotation);
  }
  glm::vec3 rotated_text_pos = rotation_matrix * glm::vec4(og_text_pos, 1);
  Vector3 text_pos = {
      .x = rotated_text_pos.x,
      .y = rotated_text_pos.y,
      .z = rotated_text_pos.z,
  };

  vutil::WaveTextConfig wcfg;
  wcfg.waveSpeed.x = wcfg.waveSpeed.y = 3.0f;
  wcfg.waveSpeed.z = 0.5f;
  wcfg.waveOffset.x = wcfg.waveOffset.y = wcfg.waveOffset.z = 0.35f;
  wcfg.waveRange.x = wcfg.waveRange.y = wcfg.waveRange.z = 0.45f;

  vutil::DrawTextWave3D(font_, display_text.c_str(), text_pos, test_font_size,
                        font_spacing, line_spacing, true, &wcfg,
                        state->total_elapsed_time_, WHITE);
  rlPopMatrix();
};

void RayButton::DefaultEvent(const GameStateUPtr &) {
  std::cout << "Click Event!!!" << std::endl;
}
