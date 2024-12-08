#ifndef DMG_GUI_PAGE_HPP_
#define DMG_GUI_PAGE_HPP_

#include "GameState.hpp"
#include "IWindow.hpp"
#include "WindowManager.hpp"

class Page : public IWindow {
public:
  Page(GamePageFlags, WindowManagerSPtr = nullptr);

  void GuiSetup() override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  bool CheckCurrentPage(const GameStateUPtr &);

  WindowManagerSPtr window_manager_ = nullptr;
  std::vector<IWindowPtr> elements_;
  bool is_page_present_ = false;

private:
  bool _page_valid_ = true;
  bool _elements_sent_ = false;
  GamePageFlags _page_ = GamePageFlags_Debug;
};

#endif
