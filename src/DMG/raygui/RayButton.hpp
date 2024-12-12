#ifndef DMG_RAYGUI_RAY_BUTTON_HPP_
#define DMG_RAYGUI_RAY_BUTTON_HPP_

#include <common.h>
#include <raylib.h>

#include "DMG/core/IGui.hpp"
#include "DMG/core/util/ColorShifting.hpp"

class RayButton : public IGui {
 public:
  RayButton();
  RayButton(char *, char *, std::string = DMG_SHADER_PATH);

  void GuiSetup() override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  void RenderText(const GameStateUPtr &);

  void (*ClickEvent)(const GameStateUPtr &) = nullptr;
  static void DefaultEvent(const GameStateUPtr &);

  Font font_;
  Shader shader_;
  Vector3 position_ = {2.0f, 20.0f, -5.0f};
  Vector3 size_ = {10.0f, 2.5f, 2.0f};
  bool button_pressed_ = false;
  ColorShifting color_shifting_;
  float render_color_[3];
  std::string fs_file_name_ = "fs-basic-color.glsl";
  std::string vs_file_name_ = "vs-basic-color.glsl";
  std::string shader_path_ = DMG_SHADER_PATH;
};

#endif
