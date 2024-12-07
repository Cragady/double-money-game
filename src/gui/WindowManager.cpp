#include "WindowManager.hpp"
#include "Button.hpp"
#include "DebugWindow.hpp"
#include "RlImGuiDemo.hpp"
#include "TextElement.hpp"
#include "events/event-functions.hpp"
#include "examples/ImGuiMyFirstTool.hpp"
#include <memory>

WindowManager::WindowManager() {
  debug_window_ = std::make_shared<DebugWindow>();

  if (include_debug_window_ && !debug_window_attached_) {
    windows.push_back(debug_window_);
    debug_window_attached_ = true;
  }

  std::shared_ptr<ImGuiMyFirstTool> my_tool =
      std::make_shared<ImGuiMyFirstTool>();
  debug_window_->CopyBoolPtrTwo(
      Dw_CbpArgs{.name = my_tool->name_, .bool_ptr = &(my_tool->open_)});
  windows.push_back(my_tool);

  std::shared_ptr<RlImGuiDemo> rlimgui_demo = std::make_shared<RlImGuiDemo>();
  debug_window_->RlimguiCtrl(Dw_CbpArgs{.name = rlimgui_demo->name_,
                                        .bool_ptr = &(rlimgui_demo->open_)});
  windows.push_back(rlimgui_demo);

  std::shared_ptr<Button> button = std::make_shared<Button>();
  button->ClickEvent = events::TestEvent;
  button->open_ = true;
  windows.push_back(button);

  std::shared_ptr<TextElement> test_text = std::make_shared<TextElement>("Hello, World!");
  test_text->open_ = true;
  windows.push_back(test_text);
}

WindowManager::~WindowManager() {}

void WindowManager::Shutdown() {
  for (const std::shared_ptr<IWindow> &window : windows) {
    window->Shutdown();
  }
}

void WindowManager::Setup() {
  for (const std::shared_ptr<IWindow> &window : windows) {
    window->Setup();
  }
}

void WindowManager::Update() {
  for (const std::shared_ptr<IWindow> &window : windows) {
    window->Update();
    window->FullRender();
  }
}
