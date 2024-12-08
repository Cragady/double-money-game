#include "page_ns.hpp"
#include "Button.hpp"
#include "Page.hpp"
#include "TextElement.hpp"
#include "events/event-functions.hpp"

#include <memory>

namespace page {
using PageSPtr = std::shared_ptr<Page>;

void CreateDebugPage(WindowManagerSPtr window_manager) {
  PageSPtr page = std::make_shared<Page>(GamePageFlags_Debug, window_manager);
  window_manager->windows_.push_back(page);

  std::shared_ptr<Button> button = std::make_shared<Button>();
  button->ClickEvent = events::TestEvent;
  page->elements_.push_back(button);
  window_manager->windows_.push_back(button);

  std::shared_ptr<TextElement> test_text =
      std::make_shared<TextElement>("Hello, World!");
  page->elements_.push_back(test_text);
  window_manager->windows_.push_back(test_text);
}
} // namespace page
