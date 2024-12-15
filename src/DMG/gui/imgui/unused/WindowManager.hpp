#ifndef DMG_GUI_IMGUI_UNUSED_WINDOW_MANAGER_HPP_
#define DMG_GUI_IMGUI_UNUSED_WINDOW_MANAGER_HPP_

#include <memory>

#include "DMG/core/GameState.hpp"
#include "DMG/core/IGuiManager.hpp"
#include "DMG/gui/DebugWindow.hpp"

class WindowManager : public IGuiManager {
 public:
  WindowManager();
  ~WindowManager();

  void Setup(const GameStateUPtr &, bool) override;
  void Update(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;

  bool include_debug_window_ = true;
  bool debug_window_attached_ = false;
  std::shared_ptr<DebugWindow> debug_window_;
};

using WindowManagerSPtr = std::shared_ptr<WindowManager>;

#endif
