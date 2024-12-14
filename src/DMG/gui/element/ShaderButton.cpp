// #include "DMG/gui/element/ShaderButton.hpp"
//
// #include "DMG/core/util/ColorShifting.hpp"
//
// // clang-format off
// #include <glad/gl.h>
// #include <GLFW/glfw3.h>
// // clang-format on
// #include <raylib.h>
//
// #include <iostream>
//
// #include "DMG/core/util/color-conversion.hpp"
// #include "imgui.h"
// #include "rlgl.h"
//
// ShaderButton::ShaderButton() {}
//
// ShaderButton::ShaderButton(char *fs_name, char *vs_name,
//                            std::string shader_path) {
//   fs_file_name_ = fs_name;
//   vs_file_name_ = vs_name;
//   shader_path_ = shader_path;
// }
//
// void ShaderButton::GuiSetup(const GameStateUPtr &state) {
//   const char *vertex_shader =
//       TextFormat("%s%s", shader_path_.c_str(), vs_file_name_.c_str());
//   const char *fragment_shader =
//       TextFormat("%s%s", shader_path_.c_str(), fs_file_name_.c_str());
//   shader_ = LoadShader(vertex_shader, fragment_shader);
// };
// void ShaderButton::DataSetup(const GameStateUPtr &state) {};
// void ShaderButton::Shutdown(const GameStateUPtr &state) {
//   UnloadShader(shader_);
// };
// void ShaderButton::Update(const GameStateUPtr &state) {
//   ColorShiftingVals delta_color =
//       color_shifting_.ShiftColor(state->delta_time_);
//   Hsv color_to_convert = Hsv {
//       .h = delta_color.val[0],
//       .s = delta_color.val[1],
//       .v = delta_color.val[2],
//   };
//   Rgb color_h = hsv2rgb(color_to_convert);
//   render_color_[0] = (float)color_h.r;
//   render_color_[1] = (float)color_h.g;
//   render_color_[1] = 1.0f;
//   render_color_[2] = (float)color_h.b;
//   render_color_[2] = 1.0f;
//   UpdateCamera(&camera_, CAMERA_ORBITAL);
// };
// void ShaderButton::BeginRender(const GameStateUPtr &state) {
//   if (!open_) return;
//
//   int color_loc = GetShaderLocation(shader_, "u_fragmentColor");
//
//   std::cout << "R: " << render_color_[0] << " G: " << render_color_[1]
//             << " B: " << render_color_[2] << std::endl;
//   // We pass reference to the zeroth index to pass a void pointer to the GL
//   BeginMode3D(camera_);
//   BeginShaderMode(shader_);
//   SetShaderValue(shader_, color_loc, &render_color_[0],
//   RL_SHADER_UNIFORM_VEC3);
//
//   render_ready_ = ImGui::Begin("Button Shader - Debug", NULL,
//                                ImGuiWindowFlags_AlwaysAutoResize);
// };
// void ShaderButton::Render(const GameStateUPtr &state) {
//   if (!open_ || !render_ready_) return;
//   ImVec2 size(1000.0f, 1000.0f);
//   // TODO: add event
//   ImGui::InvisibleButton(name_.c_str(), size);
//   ImVec2 p0 = ImGui::GetItemRectMin();
//   ImVec2 p1 = ImGui::GetItemRectMax();
//   // ImDrawList *draw_list = ImGui::GetWindowDrawList();
//   ImDrawData *draw_data = ImGui::GetDrawData();
//   float L = draw_data->DisplayPos.x;
//   float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
//   float T = draw_data->DisplayPos.y;
//   float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
//
//   const float ortho_projection[4][4] = {
//       {2.0f / (R - L), 0.0f, 0.0f, 0.0f},
//       {0.0f, 2.0f / (T - B), 0.0f, 0.0f},
//       {0.0f, 0.0f, -1.0f, 0.0f},
//       {(R + L) / (L - R), (T + B) / (B - T), 0.0f, 1.0f},
//   };
//
//   DrawRectangle(0, 0, L, R, WHITE);
//
//   // draw_list->PushClipRect(p0, p1);
//
//   // draw_list->AddCallback(
//   //     [](const ImDrawList *dl, const ImDrawCmd *cmd) {
//   //       ShaderButton *context = (ShaderButton *)cmd->UserCallbackData;
//   //       ImDrawData *draw_data = ImGui::GetDrawData();
//   //       float L = draw_data->DisplayPos.x;
//   //       float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
//   //       float T = draw_data->DisplayPos.y;
//   //       float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
//
//   //       const float ortho_projection[4][4] = {
//   //           {2.0f / (R - L), 0.0f, 0.0f, 0.0f},
//   //           {0.0f, 2.0f / (T - B), 0.0f, 0.0f},
//   //           {0.0f, 0.0f, -1.0f, 0.0f},
//   //           {(R + L) / (L - R), (T + B) / (B - T), 0.0f, 1.0f},
//   //       };
//   //       glUseProgram(context->shader_.id);
//   //       glUniformMatrix4fv(glGetUniformLocation(context->shader_.id,
//   //       "transform"), 1,
//   //                          GL_FALSE, &ortho_projection[0][0]);
//   //     },
//   //     this, sizeof(*this));
//   // draw_list->AddRectFilled(p0, p1, 0xFFFF00FF);
//   // draw_list->AddCallback([](const ImDrawList *, const ImDrawCmd *) {
//   //   glUseProgram(0);
//   // }, nullptr);
//   // draw_list->PopClipRect();
// };
// void ShaderButton::EndRender(const GameStateUPtr &state) {
//   if (!open_ || !render_ready_) return;
//   EndShaderMode();
//   EndMode3D();
//   ImGui::End();
// };
// void ShaderButton::FullRender(const GameStateUPtr &state) {
//   BeginRender(state);
//   Render(state);
//   EndRender(state);
// };
