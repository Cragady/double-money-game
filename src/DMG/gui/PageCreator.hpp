#ifndef DMG_GUI_PAGE_CREATOR_HPP_
#define DMG_GUI_PAGE_CREATOR_HPP_

#include <functional>
#include <vector>

#include "DMG/core/GameState.hpp"
#include "DMG/gui/IWindow.hpp"
#include "DMG/gui/Page.hpp"
#include "DMG/gui/WindowManager.hpp"

using PageSPtr = std::shared_ptr<Page>;
using IWindowPtrVector = std::vector<IWindowPtr>;

class PageCreator {
 public:
  PageCreator(WindowManagerSPtr = nullptr);

  bool gui_setup_ = false;
  IWindowPtrVector no_page_group_;
  IWindowPtrVector debug_page_group_;
  WindowManagerSPtr window_manager_;
  PageSPtr debug_page_;

  void Setup(const GameStateUPtr &);
  void CreateNoPageWindows(const GameStateUPtr &);
  void CreateDebugPage(const GameStateUPtr &);
  void AddWindowToCollections(IWindowPtrVector &, IWindowPtr,
                              PageSPtr = nullptr, bool = true);
  void AddAndCreate(std::function<void()> &, unsigned long *, bool = false);
};

#endif
