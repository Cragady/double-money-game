#ifndef DMG_GUI_ELEMENT_RAY_BUTTON_HPP_
#define DMG_GUI_ELEMENT_RAY_BUTTON_HPP_

#include <common.h>
#include <raylib.h>

#include "DMG/core/IGui.hpp"
#include "DMG/core/util/ColorShifting.hpp"
#include "DMG/gui/GuiObject.hpp"

class RayButton : public IGui {
 public:
  RayButton();
  RayButton(char *, char *, std::string = DMG_SHADER_PATH);

  void GuiSetup(const GameStateUPtr &) override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;
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

  GuiObject gui_object_;
  bool button_pressed_ = false;
  ColorShifting color_shifting_;
  float render_color_[3];
  std::string fs_file_name_ = "fs-basic-color.glsl";
  std::string vs_file_name_ = "vs-basic-color.glsl";
  std::string shader_path_ = DMG_SHADER_PATH;
};

#endif
