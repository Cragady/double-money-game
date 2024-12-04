#include <iostream>

#include "ButtonComponent.hpp"
#include "imgui.h"

ButtonComponent::ButtonComponent(std::string name, std::string button_text,
                                 bool is_open, ImGuiWindowFlags flags,
                                 void (*clickEvent)()) {
  name_ = name;
  component_open_ = is_open;
  render_flags_ = flags;
  button_text_ = button_text;
  ClickEvent = clickEvent;
}

ButtonComponent::~ButtonComponent() { component_open_ = false; }

void ButtonComponent::Update() {
  if (ImGui::Begin(name_.c_str(), &component_open_, render_flags_)) {
    if (ImGui::Button(button_text_.c_str())) {
      ClickEvent();
    }
  }
  ImGui::End();
}

void ButtonComponent::DefaultEvent() {
  std::cout << "Click Event!!!" << std::endl;
}
