#ifndef DMG_GUI_IMGUI_DEBUG_WINDOW_HPP_
#define DMG_GUI_IMGUI_DEBUG_WINDOW_HPP_

#include <raylib.h>

#include <memory>

#include "DMG/core/GameState.hpp"
#include "DMG/gui/imgui/IWindow.hpp"

// TODO: clean/dry this class up

struct Dw_CbpArgs {
  std::string name;
  bool *bool_ptr;
};

class ICoreObject;
class DebugWindow;
using DebugWindowSPtr = std::shared_ptr<DebugWindow>;
using ICoreObjectWPtr = std::weak_ptr<ICoreObject>;

class DebugWindow : public IWindow,
                    public std::enable_shared_from_this<DebugWindow> {
 private:
  struct Private {
    explicit Private() = default;
  };

 public:
  DebugWindow(Private);
  DebugWindow(bool *, bool *);
  ~DebugWindow();
  // Copy ctors
  DebugWindow(const DebugWindow &) = delete;
  DebugWindow &operator=(DebugWindow &) = delete;
  // Move ctors
  DebugWindow(DebugWindow &&) = delete;
  DebugWindow &operator=(DebugWindow &&) = delete;

  static DebugWindowSPtr Create();

  void GuiSetup(const GameStateUPtr &) override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  void CopyBoolPtrOne(Dw_CbpArgs ctrl_one);
  void CopyBoolPtrTwo(Dw_CbpArgs ctrl_two);
  void RlimguiCtrl(Dw_CbpArgs ctrl);
  void SetProgramFlag(Dw_CbpArgs ctrl);
  void SetProgramFlag2(Dw_CbpArgs ctrl);
  void SetObjectReference(ICoreObjectWPtr);

 private:
  bool _default_false_ = false;
  bool *_program_flag_ = nullptr;
  std::string _program_flag_show_ = "";
  bool *_program_flag_2_ = nullptr;
  std::string _program_flag_show_2_ = "";
  bool *_control_show_1_ = nullptr;
  std::string _control_1_ = "";
  bool *_control_show_2_ = nullptr;
  std::string _control_2_ = "";
  bool *_rlimgui_show_ = nullptr;
  std::string _rlimgui_name_ = "";

  std::weak_ptr<ICoreObject> _selected_object_;
  bool _editing_object_ = false;
};

#endif
