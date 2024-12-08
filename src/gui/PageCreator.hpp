#ifndef DMG_GUI_PAGE_CREATOR_HPP_
#define DMG_GUI_PAGE_CREATOR_HPP_

#include "GameState.hpp"
#include "IWindow.hpp"
#include "Page.hpp"
#include "WindowManager.hpp"
#include <vector>
#include <functional>

using PageSPtr = std::shared_ptr<Page>;

class PageCreator {
public:
  PageCreator(WindowManagerSPtr = nullptr);

  bool gui_setup_ = false;
  std::vector<IWindowPtr> debug_page_group_;
  WindowManagerSPtr window_manager_;
  PageSPtr debug_page_;

  void Setup(const GameStateUPtr &);
  void CreateDebugPage(const GameStateUPtr &);
  void AddWindowToCollections(IWindowPtr, PageSPtr, bool = true);
  void AddAndCreate(std::function<void()> &, unsigned long *, bool = false);
};

#endif
