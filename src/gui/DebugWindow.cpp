#include <iostream>
#include <terminal-colors.h>

#include "DebugWindow.hpp"
#include "GameState.hpp"
#include "imgui.h"

// TODO: clean/dry this class up

DebugWindow::DebugWindow() {
  open_ = true;
  name_ = "Debug Window";
  // flags_ = ImGuiWindowFlags_NoBackground;
}

DebugWindow::~DebugWindow() {
  open_ = false;
  Shutdown();
}

void DebugWindow::DataSetup(const GameStateUPtr &state) {}
void DebugWindow::GuiSetup() {}
void DebugWindow::Shutdown() {}
void DebugWindow::Update(const GameStateUPtr &state) {}
void DebugWindow::BeginRender(const GameStateUPtr &state) {
  render_ready_ = ImGui::Begin(name_.c_str(), &open_, flags_);
  render_ended_ = false;
}
void DebugWindow::Render(const GameStateUPtr &state) {
  render_ended_ = true;
  if (!render_ready_) {
    EndRender(state);
    return;
  }

  if (ImGui::BeginTabBar("Debug Tabs", ImGuiTabBarFlags_FittingPolicyScroll)) {
    if (ImGui::BeginTabItem("Program Control")) {
      if (_program_flag_ != nullptr) {
        if (ImGui::Button(_program_flag_show_.c_str())) {
          *_program_flag_ = !*_program_flag_;
        }
      }
      if (ImGui::Button("Reset Game State")) {
        state->reset_game_state_ = true;
      }
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Switch Game Page")) {
      bool none = state->GetGamePageFlag(GamePageFlags_None);
      bool debug = state->GetGamePageFlag(GamePageFlags_Debug);
      bool title = state->GetGamePageFlag(GamePageFlags_Title);
      bool game = state->GetGamePageFlag(GamePageFlags_Game);
      bool pause = state->GetGamePageFlag(GamePageFlags_Pause);
      bool options = state->GetGamePageFlag(GamePageFlags_Options);
      ImGui::Text("current_page_ bitmask value: %i", state->current_page_);
      ImGui::SeparatorText("Controls");
      if (ImGui::Button("None")) {
        none = false;
        debug = false;
        title = false;
        game = false;
        pause = false;
        options = false;
      }
      ImGui::Checkbox("None (For bitmask fun only(currently))", &none);
      ImGui::Checkbox("Debug Page", &debug);
      ImGui::Checkbox("Title Page", &title);
      ImGui::Checkbox("Game Page", &game);
      ImGui::Checkbox("Pause Page", &pause);
      ImGui::Checkbox("Options Page", &options);

      state->ManageGamePageFlag(GamePageFlags_None, none);
      state->ManageGamePageFlag(GamePageFlags_Debug, debug);
      state->ManageGamePageFlag(GamePageFlags_Title, title);
      state->ManageGamePageFlag(GamePageFlags_Game, game);
      state->ManageGamePageFlag(GamePageFlags_Pause, pause);
      state->ManageGamePageFlag(GamePageFlags_Options, options);

      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("RlImGui Examples")) {
      if (_rlimgui_show_ != nullptr) {
        if (ImGui::Button(_rlimgui_name_.c_str())) {
          *_rlimgui_show_ = !*_rlimgui_show_;
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

  EndRender(state);
}

void DebugWindow::EndRender(const GameStateUPtr &state) {
  if (!render_ended_)
    return;
  ImGui::End();
  render_ended_ = false;
}

void DebugWindow::FullRender(const GameStateUPtr &state) {
  BeginRender(state);
  Render(state);
  EndRender(state);
}

void DebugWindow::CopyBoolPtrOne(Dw_CbpArgs ctrl_one) {
  std::cout << TERM_YEL
      "WARN: This class is now in control of boolean "
      "resources it does not have sole ownership over." TERM_CRESET
            << std::endl;
  _control_show_1_ = ctrl_one.bool_ptr;
  _control_1_ = ctrl_one.name;
}

void DebugWindow::CopyBoolPtrTwo(Dw_CbpArgs ctrl_two) {
  std::cout << TERM_YEL
      "WARN: This class is now in control of boolean "
      "resources it does not have sole ownership over." TERM_CRESET
            << std::endl;
  _control_show_2_ = ctrl_two.bool_ptr;
  _control_2_ = ctrl_two.name;
}

void DebugWindow::RlimguiCtrl(Dw_CbpArgs ctrl) {
  std::cout << TERM_YEL
      "WARN: This class is now in control of boolean "
      "resources it does not have sole ownership over." TERM_CRESET
            << std::endl;
  _rlimgui_show_ = ctrl.bool_ptr;
  _rlimgui_name_ = ctrl.name;
}

void DebugWindow::SetProgramFlag(Dw_CbpArgs ctrl) {
  std::cout << TERM_YEL
      "WARN: This class is now in control of boolean "
      "resources it does not have sole ownership over." TERM_CRESET
            << std::endl;
  _program_flag_ = ctrl.bool_ptr;
  _program_flag_show_ = ctrl.name;
}
