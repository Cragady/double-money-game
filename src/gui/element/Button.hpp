#ifndef DMG_GUI_ELEMENT_BUTTON_HPP_
#define DMG_GUI_ELEMENT_BUTTON_HPP_

#include <string>

#include "imgui.h"
#include "IWindow.hpp"

class Button : public IWindow {
public:
  Button(std::string name = "Debug Button",
                  std::string button_text = "Tester", bool is_open = true,
                  ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
                                           ImGuiWindowFlags_NoCollapse |
                                           ImGuiWindowFlags_NoNav |
                                           ImGuiWindowFlags_NoResize |
                                           ImGuiWindowFlags_NoDecoration, // |
                                           // ImGuiWindowFlags_NoMove,
                  void (*clickEvent)() = &DefaultEvent);
  ~Button();


  void Setup() override;
  void Shutdown() override;
  void Update() override;
  void BeginRender() override;
  void Render() override;
  void EndRender() override;
  void FullRender() override;

  void (*ClickEvent)();
  static void DefaultEvent();

  std::string name_;
  std::string button_text_;
  bool component_open_;
  ImGuiWindowFlags render_flags_;
};

#endif
