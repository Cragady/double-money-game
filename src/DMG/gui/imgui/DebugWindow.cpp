#include "DMG/gui/imgui/DebugWindow.hpp"

#include <terminal-colors.h>

#include <cstdio>
#include <iostream>
#include <string>

#include "DMG/core/GameState.hpp"
#include "DMG/core/ICoreObject.hpp"
#include "DMG/gui/element/RayButton.hpp"
#include "imgui.h"

// TODO: clean/dry this class up

DebugWindow::DebugWindow(Private) {
  open_ = true;
  name_ = "Debug Window";
  // flags_ = ImGuiWindowFlags_NoBackground;
}

DebugWindowSPtr DebugWindow::Create() {
  return std::make_shared<DebugWindow>(Private());
}

DebugWindow::~DebugWindow() { open_ = false; }

void DebugWindow::DataSetup(const GameStateUPtr &state) {}
void DebugWindow::GuiSetup(const GameStateUPtr &state) {}
void DebugWindow::Shutdown(const GameStateUPtr &state) {}
void DebugWindow::Update(const GameStateUPtr &state) {
  state->debug_window_ = shared_from_this();
}
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
      if (_program_flag_2_ != nullptr) {
        if (ImGui::Button(_program_flag_show_2_.c_str())) {
          *_program_flag_2_ = !*_program_flag_2_;
        }
      }
      if (ImGui::Button("Close Game")) {
        state->hard_stop_ = true;
      }
      ImGui::EndTabItem();
    }

    if (state->is_debug_active_ && ImGui::BeginTabItem("Object Ctl")) {
      ICoreObjectSPtr selected_object = _selected_object_.lock();
      if (selected_object) {
        static char buf_dec_x[BYTE_32] = "";
        if (buf_dec_x[0] == 0) {
          std::snprintf(buf_dec_x, BYTE_32 - 1, "%f",
                        selected_object->position_.x);
          buf_dec_x[BYTE_32 - 1] = 0;
        }
        static char buf_dec_y[BYTE_32] = "";
        if (buf_dec_y[0] == 0) {
          std::snprintf(buf_dec_y, BYTE_32 - 1, "%f",
                        selected_object->position_.y);
          buf_dec_y[BYTE_32 - 1] = 0;
        }
        static char buf_dec_z[BYTE_32] = "";
        if (buf_dec_z[0] == 0) {
          std::snprintf(buf_dec_z, BYTE_32 - 1, "%f",
                        selected_object->position_.z);
          buf_dec_z[BYTE_32 - 1] = 0;
        }
        static char buf_str_name[BYTE_64] = "";
        if (buf_str_name[0] == 0) {
          std::snprintf(buf_str_name, BYTE_64 - 1, "%s",
                        selected_object->name_.c_str());
          buf_str_name[BYTE_64 - 1] = 0;

        }
        ImGui::Text("Object Name: %s", buf_str_name);
        ImGui::Text("Position: x:%f, y:%f, z:%f", selected_object->position_.x,
                    selected_object->position_.y, selected_object->position_.z);
        if (_editing_object_) {
          ImGui::InputText("Name: ", buf_str_name, BYTE_64);
          ImGui::InputText("Pos X", buf_dec_x, BYTE_32,
                           ImGuiInputTextFlags_CharsDecimal);
          ImGui::InputText("Pos Y", buf_dec_y, BYTE_32,
                           ImGuiInputTextFlags_CharsDecimal);
          ImGui::InputText("Pos Z", buf_dec_z, BYTE_32,
                           ImGuiInputTextFlags_CharsDecimal);
        }

        if (!_editing_object_) {
          if (ImGui::Button("Edit")) {
            _editing_object_ = true;
          }
        } else {
          if (ImGui::Button("Cancel")) {
            _editing_object_ = false;
          }
          if (ImGui::Button("Save")) {
            selected_object->name_ = buf_str_name;
            selected_object->position_.x = std::stof(buf_dec_x);
            selected_object->position_.y = std::stof(buf_dec_y);
            selected_object->position_.z = std::stof(buf_dec_z);
            selected_object->updateable_ = true;
          }
        }
        // _editing_object_
      } else {
        ImGui::SeparatorText("Please select an object to edit.");
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
  if (!render_ended_) return;
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

void DebugWindow::SetProgramFlag2(Dw_CbpArgs ctrl) {
  std::cout << TERM_YEL
      "WARN: This class is now in control of boolean "
      "resources it does not have sole ownership over." TERM_CRESET
            << std::endl;
  _program_flag_2_ = ctrl.bool_ptr;
  _program_flag_show_2_ = ctrl.name;
};

void DebugWindow::SetObjectReference(ICoreObjectWPtr ref) {
  _selected_object_ = ref;
}
