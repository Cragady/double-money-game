#include "DMG/raygui/MainCamera.hpp"

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include <cmath>

#include "DMG/core/GameState.hpp"
#include "DMG/core/events/event-functions.hpp"
#include "DMG/core/util/color-conversion.hpp"

MainCamera::MainCamera() {
  main_camera_ = std::make_shared<Camera>();
  main_camera_->position = (Vector3) {13.0f, 8.0f, 19.0f}; // Camera position
  main_camera_->target =
      (Vector3) {0.0f, 5.0f, 0.0f}; // Camera looking at point
  main_camera_->up = (Vector3) {
      0.0f, 1.0f, 0.0f};      // Camera up vector (rotation towards target)
  main_camera_->fovy = 45.0f; // Camera field-of-view Y
  main_camera_->projection = CAMERA_PERSPECTIVE;
  name_ = "Main Camera";
}

MainCamera::MainCamera(char *fs_name, char *vs_name, std::string shader_path)
    : MainCamera() {
  fs_file_name_ = fs_name;
  vs_file_name_ = vs_name;
  shader_path_ = shader_path;
}

void MainCamera::GuiSetup(const GameStateUPtr &state) {
  // GameStateUPtr const char *vertex_shader =
  //     TextFormat("%s%s", shader_path_.c_str(), vs_file_name_.c_str());
  const char *fragment_shader =
      TextFormat("%s%s", shader_path_.c_str(), fs_file_name_.c_str());
  // shader_ = LoadShader(vertex_shader, fragment_shader);
  shader_ = LoadShader(0, fragment_shader);

  shader_raymarch_ = LoadShader(
      // 0, TextFormat("assets/vendor/raylib/shaders/glsl%i/hybrid_raymarch.fs",
      0, TextFormat("assets/shaders/glsl%i/raymarching-simplified.glsl",
                    GLSL_VERSION));

  int diffuse_loc = GetShaderLocation(shader_raymarch_, "diffuseIntensity");
  float new_diffuse = 10.0f;
  SetShaderValue(shader_raymarch_, diffuse_loc, &new_diffuse,
                 RL_SHADER_UNIFORM_FLOAT);

  march_locs_.cam_pos = GetShaderLocation(shader_raymarch_, "camPos");
  march_locs_.cam_dir = GetShaderLocation(shader_raymarch_, "camDir");
  march_locs_.screen_center =
      GetShaderLocation(shader_raymarch_, "screenCenter");
  march_locs_.check_1 = GetShaderLocation(shader_raymarch_, "checkerColor1");
  march_locs_.check_2 = GetShaderLocation(shader_raymarch_, "checkerColor2");

  // Camera FOV is pre-calculated in the camera Distance.
  cam_dist_ = 1.0f / (tanf(main_camera_->fovy * 0.5f * DEG2RAD));

  color_shifting_.shift_speed_ = 20;

  button_.open_ = true;
  button_.color_shifting_.shift_speed_ = 40;
  button_.ClickEvent = events::TestEvent;
  button_.position_ = {2.0f, 6.6f, -5.0f};
  button_.GuiSetup(state);
}
void MainCamera::DataSetup(const GameStateUPtr &state) {
  Vector2 screenCenter = {.x = state->screen_width_ / 2.0f,
                          .y = state->screen_height_ / 2.0f};
  SetShaderValue(shader_raymarch_, march_locs_.screen_center, &screenCenter,
                 SHADER_UNIFORM_VEC2);
}
void MainCamera::Shutdown(const GameStateUPtr &state) {
  button_.Shutdown(state);
  UnloadShader(shader_);
  UnloadShader(shader_raymarch_);
}
void MainCamera::Update(const GameStateUPtr &state) {
  if (main_camera_ == nullptr) return;
  state->main_camera_ = main_camera_;

  state->mouse_ray_ = GetScreenToWorldRay(GetMousePosition(), *main_camera_);
  capture_cursor_ = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
  button_.Update(state);
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

  float mouse_sensitivity = 0.0f;
  if (capture_cursor_) {
    // UpdateCamera(&camera_, CAMERA_FREE);
    mouse_sensitivity = 0.05f;
    MouseCapture(state);
  }
  float move_speed = 0.01f;
  Vector3 movement =
      Vector3 {(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) *
                       move_speed - // Move forward-backward
                   (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * move_speed,
               (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) *
                       move_speed - // Move right-left
                   (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * move_speed,
               (IsKeyDown(KEY_SPACE)) * move_speed -
                   (IsKeyDown(KEY_LEFT_CONTROL)) * move_speed};
  UpdateCameraPro(&(*main_camera_), movement,
                  (Vector3) {
                      GetMouseDelta().x * mouse_sensitivity, // Rotation: yaw
                      GetMouseDelta().y * mouse_sensitivity, // Rotation: pitch
                      0.0f                                   // Rotation: roll
                  },
                  GetMouseWheelMove() * 2.0f);

  // Update Camera Postion in the ray march shader.
  SetShaderValue(shader_raymarch_, march_locs_.cam_pos,
                 &(main_camera_->position), RL_SHADER_UNIFORM_VEC3);

  color_to_convert.h += 180;
  color_to_convert.v = 1.0f;
  Rgb color_checks_1 = hsv2rgb(color_to_convert);
  color_to_convert.v = 0.5f;
  Rgb color_checks_2 = hsv2rgb(color_to_convert);
  float checks_1[4] = {(float)color_checks_1.r, (float)color_checks_1.g,
                       (float)color_checks_1.b, 1.0f};
  float checks_2[4] = {(float)color_checks_2.r, (float)color_checks_2.g,
                       (float)color_checks_2.b, 1.0f};

  SetShaderValue(shader_raymarch_, march_locs_.check_1, &checks_1[0],
                 RL_SHADER_UNIFORM_VEC4);
  SetShaderValue(shader_raymarch_, march_locs_.check_2, &checks_2[0],
                 RL_SHADER_UNIFORM_VEC4);

  // Update Camera Looking Vector. Vector length determines FOV.
  Vector3 camDir =
      Vector3Scale(Vector3Normalize(Vector3Subtract(main_camera_->target,
                                                    main_camera_->position)),
                   cam_dist_);
  SetShaderValue(shader_raymarch_, march_locs_.cam_dir, &(camDir),
                 RL_SHADER_UNIFORM_VEC3);
}
void MainCamera::BeginRender(const GameStateUPtr &) {}
void MainCamera::Render(const GameStateUPtr &) {}
void MainCamera::EndRender(const GameStateUPtr &) {}
void MainCamera::FullRender(const GameStateUPtr &) {}

void MainCamera::BeginCamera(const GameStateUPtr &state) {
  if (main_camera_ == nullptr) return;
  BeginMode3D(*main_camera_);
}
void MainCamera::RenderCamera(const GameStateUPtr &state) {
  DrawFloor(state);
  button_.FullRender(state);
}
void MainCamera::EndCamera(const GameStateUPtr &state) { EndMode3D(); }

void MainCamera::DrawFloor(const GameStateUPtr &state) {
  if (main_camera_ == nullptr) return;
  EndMode3D();

  rlEnableDepthTest(); // Manually enable Depth Test to handle multiple
                       // rendering methods.
  BeginShaderMode(shader_raymarch_);
  DrawRectangleRec((Rectangle) {0, 0, (float)state->screen_width_,
                                (float)state->screen_height_},
                   WHITE);
  EndShaderMode();

  BeginMode3D(*main_camera_);
  BeginShaderMode(shader_);
  int color_loc = GetShaderLocation(shader_, "u_fragmentColor");

  SetShaderValue(shader_, color_loc, &render_color_[0], RL_SHADER_UNIFORM_VEC3);
  DrawGrid(200, 10.0f);
  EndShaderMode();
};

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
