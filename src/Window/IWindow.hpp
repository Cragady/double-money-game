#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "imgui.h"
#include <raylib.h>
#include <string>

class IWindow {
public:
  virtual void Setup() = 0;
  virtual void Shutdown() = 0;
  virtual void Update() = 0;
  virtual void BeginRender() = 0;
  virtual void Render() = 0;
  virtual void EndRender() = 0;
  virtual void FullRender() = 0;

  bool render_ready_ = false;
  bool render_ended_ = false;
  bool open_ = false;
  RenderTexture texture_;
  bool focused_ = false;
  Rectangle content_rect_ = {0};
  std::string name_ = "";
  ImGuiWindowFlags flags_ = ImGuiWindowFlags_None;
};

#endif
