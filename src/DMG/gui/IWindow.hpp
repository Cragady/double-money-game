#ifndef DMG_GUI_I_WINDOW_HPP_
#define DMG_GUI_I_WINDOW_HPP_

#include "DMG/core/GameState.hpp"
#include "imgui.h"
#include <memory>
#include <raylib.h>
#include <string>

class IWindow {
public:
  virtual ~IWindow(){};
  virtual void GuiSetup() = 0;
  virtual void DataSetup(const GameStateUPtr &) = 0;
  virtual void Shutdown() = 0;
  virtual void Update(const GameStateUPtr &) = 0;
  virtual void BeginRender(const GameStateUPtr &) = 0;
  virtual void Render(const GameStateUPtr &) = 0;
  virtual void EndRender(const GameStateUPtr &) = 0;
  virtual void FullRender(const GameStateUPtr &) = 0;

  RenderTexture view_texture_;
  bool render_ready_ = false;
  bool render_ended_ = false;
  bool open_ = false;
  RenderTexture texture_;
  bool focused_ = false;
  Rectangle content_rect_ = {0};
  std::string name_ = "Debug";
  ImGuiWindowFlags flags_ = ImGuiWindowFlags_None;
};

using IWindowPtr = std::shared_ptr<IWindow>;

#endif
