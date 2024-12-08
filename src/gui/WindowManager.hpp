#ifndef DMG_GUI_WINDOW_MANAGER_HPP_
#define DMG_GUI_WINDOW_MANAGER_HPP_

#include "DebugWindow.hpp"
#include "GameState.hpp"
#include "IWindow.hpp"
#include <memory>
#include <vector>

class WindowManager {
public:
  WindowManager();
  ~WindowManager();

  void Setup();
  void Update(const GameStateUPtr &);
  void Shutdown();

  bool include_debug_window_ = true;
  bool debug_window_attached_ = false;
  std::vector<IWindowPtr> windows_;
  std::shared_ptr<DebugWindow> debug_window_;
};

using WindowManagerSPtr = std::shared_ptr<WindowManager>;

#endif
