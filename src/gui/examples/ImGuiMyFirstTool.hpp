#ifndef DMG_GUI_EXAMPLES_IMGUI_MY_FIRST_TOOL_HPP_
#define DMG_GUI_EXAMPLES_IMGUI_MY_FIRST_TOOL_HPP_

#include "IWindow.hpp"

class ImGuiMyFirstTool : public IWindow {
public:
  ImGuiMyFirstTool();

  void Setup() override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;
};

#endif
