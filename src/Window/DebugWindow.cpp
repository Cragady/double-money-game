#include <iostream>
#include <terminal-colors.h>

#include "DebugWindow.hpp"
#include "imgui.h"

DebugWindow::DebugWindow() {
  open_ = true;
  name_ = "Debug Window";
  // flags_ = ImGuiWindowFlags_NoBackground;
  Setup();
}

DebugWindow::~DebugWindow() {
  open_ = false;
  Shutdown();
}

void DebugWindow::Setup() {}
void DebugWindow::Shutdown() {}
void DebugWindow::Update() {}
void DebugWindow::Render() {
  bool window_started = ImGui::Begin(name_.c_str(), &open_, flags_);
  if (!window_started) {
    EndRender();
    return;
  }

  if (_control_show_1_ != nullptr) {
    if (ImGui::Button(_control_1_.c_str())) {
      *_control_show_1_ = !*_control_show_1_;
    }
  }
  if (_control_show_2_ != nullptr) {
    if (ImGui::Button(_control_2_.c_str())) {
      *_control_show_2_ = !*_control_show_2_;
    }
  }

  EndRender();
}

void DebugWindow::EndRender() {
  ImGui::End();
}

void DebugWindow::CopyBoolPtrs(Dw_CbpArgs ctrl_one, Dw_CbpArgs ctrl_two) {
  std::cout << TERM_YEL "WARN: This class is now in control of boolean "
                        "resources it does not have sole ownership over."
            << std::endl;
  _control_show_1_ = ctrl_one.bool_ptr;
  _control_1_ = ctrl_one.name;
  _control_show_2_ = ctrl_two.bool_ptr;
  _control_2_ = ctrl_two.name;
}

