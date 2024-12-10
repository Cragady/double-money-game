#include "DMG/gui/element/Button.hpp"

#include <iostream>

#include "DMG/core/GameState.hpp"
#include "imgui.h"

Button::Button(std::string name, std::string button_text, bool is_open,
               ImGuiWindowFlags flags,
               void (*clickEvent)(const GameStateUPtr &)) {
  name_ = name;
  open_ = is_open;
  render_flags_ = flags;
  button_text_ = button_text;
  ClickEvent = clickEvent;
}

Button::~Button() { open_ = false; }

void Button::GuiSetup() {}
void Button::DataSetup(const GameStateUPtr &state) {}
void Button::Shutdown() {};
void Button::Update(const GameStateUPtr &state) {};
void Button::BeginRender(const GameStateUPtr &state) {};
void Button::Render(const GameStateUPtr &state) {};
void Button::EndRender(const GameStateUPtr &state) {};

void Button::FullRender(const GameStateUPtr &state) {
  if (!open_) return;

  float hue = 1 * 0.05f;
  ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                        (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                        (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
  if (ImGui::Begin(name_.c_str(), &open_, render_flags_)) {
    if (ImGui::Button(button_text_.c_str())) {
      ClickEvent(state);
    }
  }
  ImGui::End();
  ImGui::PopStyleColor(3);
  ImGui::PopStyleVar();
}

void Button::DefaultEvent(const GameStateUPtr &) {
  std::cout << "Click Event!!!" << std::endl;
}
