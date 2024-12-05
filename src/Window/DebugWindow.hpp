#ifndef DEBUG_WINDOW_HPP
#define DEBUG_WINDOW_HPP

#include <raylib.h>
#include "IWindow.hpp"

typedef struct Dw_CbpArgs {
  std::string name;
  bool *bool_ptr;
} DebugWindow_Control;

class DebugWindow : public IWindow {
public:
  DebugWindow();
  DebugWindow(bool *, bool *);
  ~DebugWindow();
  // Copy deletions
  DebugWindow (const DebugWindow &) = delete;
  DebugWindow &operator = (DebugWindow &) = delete;
  // Move deletions
  DebugWindow (DebugWindow &&) = delete;
  DebugWindow &operator = (DebugWindow &&) = delete;

  void Setup() override;
  void Shutdown() override;
  void Update() override;
  void BeginRender() override;
  void Render() override;
  void EndRender() override;
  void FullRender() override;

  void CopyBoolPtrs(Dw_CbpArgs ctrl_one, Dw_CbpArgs ctrl_two);
  void SetProgramFlag(Dw_CbpArgs ctrl);

private:
  bool _default_false_ = false;
  bool *_program_flag_ = nullptr;
  std::string _program_flag_show_ = "";
  bool *_control_show_1_ = nullptr;
  std::string _control_1_ = "";
  bool *_control_show_2_ = nullptr;
  std::string _control_2_ = "";
};

#endif
