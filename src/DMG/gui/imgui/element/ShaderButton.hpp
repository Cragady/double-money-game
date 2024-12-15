// #ifndef DMG_GUI_IMGUI_ELEMENT_SHADER_BUTTON_HPP_
// #define DMG_GUI_IMGUI_ELEMENT_SHADER_BUTTON_HPP_
//
// #include <common.h>
//
// #include <string>
//
// #include "DMG/core/util/ColorShifting.hpp"
// #include "DMG/gui/imgui/IWindow.hpp"
//
// class ShaderButton : public IWindow {
//  public:
//   ShaderButton();
//   ShaderButton(char *, char *, std::string = DMG_SHADER_PATH);
//
//   void GuiSetup(const GameStateUPtr &) override;
//   void DataSetup(const GameStateUPtr &) override;
//   void Shutdown(const GameStateUPtr &) override;
//   void Update(const GameStateUPtr &) override;
//   void BeginRender(const GameStateUPtr &) override;
//   void Render(const GameStateUPtr &) override;
//   void EndRender(const GameStateUPtr &) override;
//   void FullRender(const GameStateUPtr &) override;
//
//   Camera camera_ {
//       .position = (Vector3) {2.0f, 2.0f, 3.0f}, // Camera position
//       .target = (Vector3) {0.0f, 0.5f, 0.0f},   // Camera looking at point
//       .up = (Vector3) {0.0f, 1.0f,
//                        0.0f}, // Camera up vector (rotation towards target)
//       .fovy = 45.0f,          // Camera field-of-view Y
//       .projection = CAMERA_PERSPECTIVE // Camera projection type
//   };
//   Shader shader_;
//   ColorShifting color_shifting_;
//   float render_color_[3];
//   std::string fs_file_name_ = "fs-basic-color.glsl";
//   std::string vs_file_name_ = "vs-basic-color.glsl";
//   std::string shader_path_ = DMG_SHADER_PATH;
// };
//
// #endif
