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
  virtual void Render() = 0;
  virtual void EndRender() = 0;

  bool open_ = false;
  RenderTexture texture_;
  bool focused_ = false;
  Rectangle content_rect_ = {0};
  std::string name_ = "";
  ImGuiWindowFlags flags_ = ImGuiWindowFlags_None;
};

#endif
