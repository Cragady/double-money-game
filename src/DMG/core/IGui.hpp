#ifndef DMG_CORE_I_GUI_HPP_
#define DMG_CORE_I_GUI_HPP_

#include <raylib.h>

#include <memory>
#include <string>

#include "DMG/core/GameState.hpp"

class IGui {
 public:
  virtual ~IGui() {};
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
};

using IGuiPtr = std::shared_ptr<IGui>;

#endif
