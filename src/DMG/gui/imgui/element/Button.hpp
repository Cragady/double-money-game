#ifndef DMG_GUI_IMGUI_ELEMENT_BUTTON_HPP_
#define DMG_GUI_IMGUI_ELEMENT_BUTTON_HPP_

#include <string>

#include "DMG/gui/imgui/IWindow.hpp"
#include "imgui.h"

class Button : public IWindow {
 public:
  Button(std::string name = "Debug Button", std::string button_text = "Tester",
         bool is_open = false,
         ImGuiWindowFlags flags =
             ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse |
             ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoResize |
             ImGuiWindowFlags_NoDecoration, // |
                                            // ImGuiWindowFlags_NoMove,
         void (*clickEvent)(const GameStateUPtr &) = &DefaultEvent);
  ~Button();

  void GuiSetup(const GameStateUPtr &) override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  void (*ClickEvent)(const GameStateUPtr &);
  static void DefaultEvent(const GameStateUPtr &);

  std::string name_;
  std::string button_text_;
  ImGuiWindowFlags render_flags_;
};

#endif
