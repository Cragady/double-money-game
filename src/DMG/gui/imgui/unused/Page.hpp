// #ifndef DMG_GUI_IMGUI_UNUSED_PAGE_HPP_
// #define DMG_GUI_IMGUI_UNUSED_PAGE_HPP_
//
// #include "DMG/core/GameState.hpp"
// #include "DMG/core/IGui.hpp"
// #include "DMG/gui/imgui/unused/WindowManager.hpp"
//
// class Page : public IGui {
//  public:
//   Page(GamePageFlags, WindowManagerSPtr = nullptr);
//
//   void GuiSetup(const GameStateUPtr &) override;
//   void DataSetup(const GameStateUPtr &) override;
//   void Shutdown(const GameStateUPtr &) override;
//   void Update(const GameStateUPtr &) override;
//   void BeginRender(const GameStateUPtr &) override;
//   void Render(const GameStateUPtr &) override;
//   void EndRender(const GameStateUPtr &) override;
//   void FullRender(const GameStateUPtr &) override;
//
//   bool CheckCurrentPage(const GameStateUPtr &);
//
//   WindowManagerSPtr window_manager_ = nullptr;
//   std::vector<IGuiSPtr> elements_;
//   bool is_page_present_ = false;
//
//  private:
//   bool _page_valid_ = true;
//   bool _elements_sent_ = false;
//   GamePageFlags _page_ = GamePageFlags_Debug;
// };
//
// #endif
