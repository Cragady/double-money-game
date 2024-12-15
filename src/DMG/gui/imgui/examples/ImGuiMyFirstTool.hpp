#ifndef DMG_GUI_IMGUI_EXAMPLES_IMGUI_MY_FIRST_TOOL_HPP_
#define DMG_GUI_IMGUI_EXAMPLES_IMGUI_MY_FIRST_TOOL_HPP_

#include "DMG/gui/imgui/IWindow.hpp"

class ImGuiMyFirstTool : public IWindow {
 public:
  ImGuiMyFirstTool();

  void GuiSetup(const GameStateUPtr &) override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;
};

#endif
