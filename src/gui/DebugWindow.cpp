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
void DebugWindow::BeginRender() {
  render_ready_ = ImGui::Begin(name_.c_str(), &open_, flags_);
  render_ended_ = false;
}
void DebugWindow::Render() {
  render_ended_ = true;
  if (!render_ready_) {
    EndRender();
    return;
  }

  if (ImGui::BeginTabBar("Debugg Tabs", ImGuiTabBarFlags_FittingPolicyScroll)) {
    if (ImGui::BeginTabItem("Program Control")) {
      if (_program_flag_ != nullptr) {
        if (ImGui::Button(_program_flag_show_.c_str())) {
          *_program_flag_ = !*_program_flag_;
        }
      }
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Miscellaneous Control")) {
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
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  EndRender();
}

void DebugWindow::EndRender() {
  if (!render_ended_)
    return;
  ImGui::End();
  render_ended_ = false;
}

void DebugWindow::FullRender() {
  BeginRender();
  Render();
  EndRender();
}

void DebugWindow::CopyBoolPtrOne(Dw_CbpArgs ctrl_one) {
  std::cout << TERM_YEL "WARN: This class is now in control of boolean "
                        "resources it does not have sole ownership over."
            << std::endl;
  _control_show_1_ = ctrl_one.bool_ptr;
  _control_1_ = ctrl_one.name;
}


void DebugWindow::CopyBoolPtrTwo(Dw_CbpArgs ctrl_two) {
  std::cout << TERM_YEL "WARN: This class is now in control of boolean "
                        "resources it does not have sole ownership over."
            << std::endl;
  _control_show_2_ = ctrl_two.bool_ptr;
  _control_2_ = ctrl_two.name;
}

void DebugWindow::SetProgramFlag(Dw_CbpArgs ctrl) {
  std::cout << TERM_YEL "WARN: This class is now in control of boolean "
                        "resources it does not have sole ownership over."
            << std::endl;
  _program_flag_ = ctrl.bool_ptr;
  _program_flag_show_ = ctrl.name;
}
