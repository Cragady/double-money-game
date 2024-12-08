#include "Page.hpp"

Page::Page(GamePageFlags page_flag, WindowManagerSPtr window_manager) {
  window_manager_ = window_manager;
  _page_ = page_flag;
  name_ = "Debug - Page";
}

void Page::DataSetup(const GameStateUPtr &state) {}
void Page::GuiSetup() {
  if (window_manager_ == nullptr) {
    _page_valid_ = false;
    return;
  }
};

void Page::Shutdown() {
  if (!_page_valid_)
    return;
};
void Page::Update(const GameStateUPtr &state) {
  if (!_page_valid_)
    return;
  CheckCurrentPage(state);
  for (const IWindowPtr &element : elements_) {
    element->open_ = is_page_present_;
  }
};
void Page::BeginRender(const GameStateUPtr &state) {};
void Page::Render(const GameStateUPtr &state) {};
void Page::EndRender(const GameStateUPtr &state) {};
void Page::FullRender(const GameStateUPtr &state) {
  if (!is_page_present_ || !_page_valid_)
    return;

  BeginRender(state);
  Render(state);
  EndRender(state);
};

bool Page::CheckCurrentPage(const GameStateUPtr &state) {
  is_page_present_ = state->GetGamePageFlag(_page_);
  return is_page_present_;
}
