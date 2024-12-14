#ifndef DMG_CORE_I_GUI_HPP_
#define DMG_CORE_I_GUI_HPP_

#include <raylib.h>

#include <memory>
#include <string>

#include "DMG/core/GameState.hpp"

class IGui {
 public:
  virtual ~IGui() {};
  // NOTE: any setup that uses the game state in 'GuiSetup' should refresh that
  // same reference or value within 'DataSetup'
  // NOTE: I took a trip to stupidville adding GameStateUPtr to GuiSetup. There
  // shouldn't be a reason to use game state here, but I suppose if it's
  // absolutely necessary, then it's there for ya.
  virtual void GuiSetup(const GameStateUPtr &) = 0;
  virtual void DataSetup(const GameStateUPtr &) = 0;
  virtual void Shutdown(const GameStateUPtr &) = 0;
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
