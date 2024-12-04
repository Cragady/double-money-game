#include <iostream>

#include "ButtonComponent.hpp"
#include "imgui.h"

ButtonComponent::ButtonComponent(std::string name, std::string button_text,
                                 bool is_open, ImGuiWindowFlags flags) {
  name_ = name;
  component_open_ = is_open;
  render_flags_ = flags;
  button_text_ = button_text;
}

ButtonComponent::~ButtonComponent() { component_open_ = false; }

void ButtonComponent::Update() {
  if (ImGui::Begin(name_.c_str(), &component_open_, render_flags_)) {
    if (ImGui::Button(button_text_.c_str())) {
      std::cout << "Clicked!!!" << std::endl;
    }
  }
  ImGui::End();
}
