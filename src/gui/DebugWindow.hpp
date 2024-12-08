#ifndef DMG_GUI_DEBUG_WINDOW_HPP_
#define DMG_GUI_DEBUG_WINDOW_HPP_

#include "GameState.hpp"
#include "IWindow.hpp"
#include <raylib.h>

// TODO: clean/dry this class up

struct Dw_CbpArgs {
  std::string name;
  bool *bool_ptr;
};

class DebugWindow : public IWindow {
public:
  DebugWindow();
  DebugWindow(bool *, bool *);
  ~DebugWindow();
  // Copy ctors
  DebugWindow(const DebugWindow &) = delete;
  DebugWindow &operator=(DebugWindow &) = delete;
  // Move ctors
  DebugWindow(DebugWindow &&) = delete;
  DebugWindow &operator=(DebugWindow &&) = delete;

  void GuiSetup() override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  void CopyBoolPtrOne(Dw_CbpArgs ctrl_one);
  void CopyBoolPtrTwo(Dw_CbpArgs ctrl_two);
  void RlimguiCtrl(Dw_CbpArgs ctrl);
  void SetProgramFlag(Dw_CbpArgs ctrl);

private:
  bool _default_false_ = false;
  bool *_program_flag_ = nullptr;
  std::string _program_flag_show_ = "";
  bool *_control_show_1_ = nullptr;
  std::string _control_1_ = "";
  bool *_control_show_2_ = nullptr;
  std::string _control_2_ = "";
  bool *_rlimgui_show_ = nullptr;
  std::string _rlimgui_name_ = "";
};

#endif
