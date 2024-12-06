#ifndef BUTTON_COMPONENT_HPP
#define BUTTON_COMPONENT_HPP

#include <string>

#include "imgui.h"

class ButtonComponent {
public:
  ButtonComponent(std::string name = "Debug Button",
                  std::string button_text = "Tester", bool is_open = true,
                  ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
                                           ImGuiWindowFlags_NoCollapse |
                                           ImGuiWindowFlags_NoNav |
                                           ImGuiWindowFlags_NoResize |
                                           ImGuiWindowFlags_NoDecoration, // |
                                           // ImGuiWindowFlags_NoMove,
                  void (*clickEvent)() = &DefaultEvent);
  ~ButtonComponent();
  void Update();
  void (*ClickEvent)();
  static void DefaultEvent();

  std::string name_;
  std::string button_text_;
  bool component_open_;
  ImGuiWindowFlags render_flags_;
};

#endif
