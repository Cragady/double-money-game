#ifndef DMG_GUI_WINDOW_MANAGER_HPP_
#define DMG_GUI_WINDOW_MANAGER_HPP_

#include "DebugWindow.hpp"
#include "IWindow.hpp"
#include <memory>
#include <vector>
class WindowManager {
public:
  WindowManager();
  ~WindowManager();

  void Setup();
  void Update();

  bool include_debug_window_ = true;
  bool debug_window_attached_ = false;
  std::vector<std::shared_ptr<IWindow>> windows;
  std::shared_ptr<DebugWindow> debug_window_;
};

#endif
