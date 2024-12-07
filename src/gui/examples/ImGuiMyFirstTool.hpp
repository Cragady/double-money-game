#ifndef DMG_GUI_EXAMPLES_IMGUI_MY_FIRST_TOOL_HPP_
#define DMG_GUI_EXAMPLES_IMGUI_MY_FIRST_TOOL_HPP_

#include "IWindow.hpp"

class ImGuiMyFirstTool : public IWindow {
public:
  ImGuiMyFirstTool();

  void Setup() override;
  void Shutdown() override;
  void Update() override;
  void BeginRender() override;
  void Render() override;
  void EndRender() override;
  void FullRender() override;
};

#endif
