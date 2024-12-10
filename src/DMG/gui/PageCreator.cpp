#include "DMG/gui/PageCreator.hpp"

#include <functional>

#include "DMG/core/events/event-functions.hpp"
#include "DMG/gui/Page.hpp"
#include "DMG/gui/WindowManager.hpp"
#include "DMG/gui/element/Button.hpp"
#include "DMG/gui/element/TextElement.hpp"

PageCreator::PageCreator(WindowManagerSPtr window_manager) {
  window_manager_ = window_manager;
};

void PageCreator::Setup(const GameStateUPtr &state) {
  if (window_manager_ == nullptr) return;

  CreateDebugPage(state);
};

void PageCreator::CreateDebugPage(const GameStateUPtr &state) {
  debug_page_ = std::make_shared<Page>(GamePageFlags_Debug, window_manager_);
  unsigned long current_element = 0;

  std::function<void()> lambda = [this]() {
    AddWindowToCollections(debug_page_, debug_page_, false);
  };
  AddAndCreate(lambda, &current_element, true);

  lambda = [this]() {
    std::shared_ptr<Button> button = std::make_shared<Button>();
    button->ClickEvent = events::TestRandom;
    AddWindowToCollections(button, debug_page_);
  };
  AddAndCreate(lambda, &current_element);

  lambda = [this]() {
    std::shared_ptr<TextElement<void>> test_text =
        std::make_shared<TextElement<void>>("Hello, World!");
    AddWindowToCollections(test_text, debug_page_);
  };
  AddAndCreate(lambda, &current_element);

  lambda = [this]() {
    std::shared_ptr<TextElement<long double>> current_money =
        std::make_shared<TextElement<long double>>("Hello, World!",
                                                   "Debug - Current Money");
    AddWindowToCollections(current_money, debug_page_);
  };
  AddAndCreate(lambda, &current_element);
  TextElement<long double> *current_money =
      (TextElement<long double> *)debug_page_group_[current_element].get();

  current_money->data_ptr_ = &(state->current_money_);

  lambda = [this]() {
    std::shared_ptr<Button> add_money =
        std::make_shared<Button>("Debug - Add Money", "Add Money");
    AddWindowToCollections(add_money, debug_page_);
  };
  AddAndCreate(lambda, &current_element);
  Button *add_money = (Button *)debug_page_group_[current_element].get();
  add_money->ClickEvent = events::AddMoneyEvent;
};

void PageCreator::AddWindowToCollections(IWindowPtr window, PageSPtr page,
                                         bool add_to_page) {
  debug_page_group_.push_back(window);
  if (add_to_page) page->elements_.push_back(window);
  window_manager_->windows_.push_back(window);
};

void PageCreator::AddAndCreate(std::function<void()> &func,
                               unsigned long *current_element,
                               bool first_element) {
  if (!first_element) {
    (*current_element)++;
  }
  if (gui_setup_) return;
  func();
}
