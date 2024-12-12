#ifndef DMG_RAYGUI_MAIN_CAMERA_HPP_
#define DMG_RAYGUI_MAIN_CAMERA_HPP_

#include <common.h>

#include "DMG/core/GameState.hpp"
#include "DMG/core/IGui.hpp"
#include "DMG/core/util/ColorShifting.hpp"
#include "DMG/raygui/RayButton.hpp"

class MainCamera : public IGui {
 public:
  MainCamera();
  MainCamera(char *, char *, std::string = DMG_SHADER_PATH);

  void GuiSetup() override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  void BeginCamera(const GameStateUPtr &);
  void RenderCamera(const GameStateUPtr &);
  void EndCamera(const GameStateUPtr &);

  void MouseCapture(const GameStateUPtr &);
  void CorrectMouse(const GameStateUPtr &, Vector2, Vector2);

  RayButton button_;
  Shader shader_;
  ColorShifting color_shifting_;
  Camera camera_ = {0};
  bool capture_cursor_ = false;
  float render_color_[3];
  std::string fs_file_name_ = "fs-basic-color.glsl";
  std::string vs_file_name_ = "vs-basic-color.glsl";
  std::string shader_path_ = DMG_SHADER_PATH;
};

#endif
