#include "DMG/raygui/MainCamera.hpp"

#include <raylib.h>
#include <rlgl.h>

#include "DMG/core/GameState.hpp"
#include "DMG/core/util/color-conversion.hpp"

MainCamera::MainCamera() {
  camera_.position = (Vector3) {50.0f, 50.0f, 50.0f}; // Camera position
  camera_.target = (Vector3) {0.0f, 10.0f, 0.0f};     // Camera looking at point
  camera_.up = (Vector3) {0.0f, 1.0f,
                          0.0f}; // Camera up vector (rotation towards target)
  camera_.fovy = 45.0f;          // Camera field-of-view Y
  camera_.projection = CAMERA_PERSPECTIVE;
  name_ = "Main Camera";
}

MainCamera::MainCamera(char *fs_name, char *vs_name, std::string shader_path)
    : MainCamera() {
  fs_file_name_ = fs_name;
  vs_file_name_ = vs_name;
  shader_path_ = shader_path;
}

void MainCamera::GuiSetup() {
  // const char *vertex_shader =
  //     TextFormat("%s%s", shader_path_.c_str(), vs_file_name_.c_str());
  const char *fragment_shader =
      TextFormat("%s%s", shader_path_.c_str(), fs_file_name_.c_str());
  // shader_ = LoadShader(vertex_shader, fragment_shader);
  shader_ = LoadShader(0, fragment_shader);
}
void MainCamera::DataSetup(const GameStateUPtr &) {}
void MainCamera::Shutdown() { UnloadShader(shader_); }
void MainCamera::Update(const GameStateUPtr &state) {
  capture_cursor_ = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
  color_shifting_.ShiftColor(state->delta_time_);
  Hsv color_to_convert = Hsv {
      .h = color_shifting_.colors_[0],
      .s = 1,
      .v = 0.25,
  };
  Rgb color_h = hsv2rgb(color_to_convert);
  render_color_[0] = (float)color_h.r;
  render_color_[1] = (float)color_h.g;
  render_color_[2] = (float)color_h.b;

  if (capture_cursor_) {
    UpdateCamera(&camera_, CAMERA_FIRST_PERSON);
    MouseCapture(state);
  }
}
void MainCamera::BeginRender(const GameStateUPtr &) {}
void MainCamera::Render(const GameStateUPtr &) {}
void MainCamera::EndRender(const GameStateUPtr &) {}
void MainCamera::FullRender(const GameStateUPtr &) {}

void MainCamera::BeginCamera(const GameStateUPtr &state) {
  BeginMode3D(camera_);
}
void MainCamera::RenderCamera(const GameStateUPtr &state) {
  BeginShaderMode(shader_);
  int color_loc = GetShaderLocation(shader_, "u_fragmentColor");

  SetShaderValue(shader_, color_loc, &render_color_[0], RL_SHADER_UNIFORM_VEC3);
  DrawGrid(200, 10.0f);
  EndShaderMode();
}
void MainCamera::EndCamera(const GameStateUPtr &state) { EndMode3D(); }

void MainCamera::MouseCapture(const GameStateUPtr &state) {
  if (!capture_cursor_) return;

  Vector2 mouse_pos = GetMousePosition();
  Vector2 mouse_delta = GetMouseDelta();
  Vector2 calculated_mouse_pos = Vector2 {
      .x = (float)mouse_pos.x + mouse_delta.x,
      .y = (float)mouse_pos.y + mouse_delta.y,
  };
  if (IsCursorOnScreen()) {
    CorrectMouse(state, calculated_mouse_pos, mouse_pos);
  }
  if (!IsCursorOnScreen()) {
    CorrectMouse(state, calculated_mouse_pos, mouse_pos);
  }
}

void MainCamera::CorrectMouse(const GameStateUPtr &state,
                              Vector2 calculated_mouse_pos, Vector2 mouse_pos) {
  int mouse_correction_x = mouse_pos.x;
  int mouse_correction_y = mouse_pos.y;
  int x_bounds = GetScreenWidth() - 1;
  int y_bounds = GetScreenHeight() - 1;

  if (calculated_mouse_pos.x == 0) {
    mouse_correction_x = 1;
  }
  if (calculated_mouse_pos.x == x_bounds) {
    mouse_correction_x = x_bounds - 1;
  }
  if (calculated_mouse_pos.y == 0) {
    mouse_correction_y = 1;
  }
  if (calculated_mouse_pos.y == y_bounds) {
    mouse_correction_y = y_bounds - 1;
  }
  if (calculated_mouse_pos.x > x_bounds) {
    mouse_correction_x = 1;
  }
  if (calculated_mouse_pos.x < 0) {
    mouse_correction_x = x_bounds - 1;
  }
  if (calculated_mouse_pos.y > y_bounds) {
    mouse_correction_y = 1;
  }
  if (calculated_mouse_pos.y < 0) {
    mouse_correction_y = y_bounds - 1;
  }

  if (mouse_correction_y != mouse_pos.y || mouse_correction_x != mouse_pos.x) {
    SetMousePosition(mouse_correction_x, mouse_correction_y);
  }
}
