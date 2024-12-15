#ifndef DMG_GUI_IMGUI_I_WINDOW_HPP_
#define DMG_GUI_IMGUI_I_WINDOW_HPP_

#include <raylib.h>

#include <memory>

#include "DMG/core/IGui.hpp"
#include "imgui.h"

class IWindow : public IGui {
 public:
  virtual ~IWindow() {};

  ImGuiWindowFlags flags_ = ImGuiWindowFlags_None;
};

using IWindowPtr = std::shared_ptr<IWindow>;

#endif
