#include <iostream>

#include "Button.hpp"
#include "imgui.h"

Button::Button(std::string name, std::string button_text,
                                 bool is_open, ImGuiWindowFlags flags,
                                 void (*clickEvent)()) {
  name_ = name;
  component_open_ = is_open;
  render_flags_ = flags;
  button_text_ = button_text;
  ClickEvent = clickEvent;
}

Button::~Button() { component_open_ = false; }

void Button::Setup() {};
void Button::Shutdown() {};
void Button::Update() {};
void Button::BeginRender() {};
void Button::Render() {};
void Button::EndRender() {};

void Button::FullRender() {

  float hue = 1 * 0.05f;
  ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                        (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                        (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
  if (ImGui::Begin(name_.c_str(), &component_open_, render_flags_)) {
    if (ImGui::Button(button_text_.c_str())) {
      ClickEvent();
    }
  }
  ImGui::End();
  ImGui::PopStyleColor(3);
  ImGui::PopStyleVar();
}

void Button::DefaultEvent() {
  std::cout << "Click Event!!!" << std::endl;
}
