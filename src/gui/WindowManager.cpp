#include "WindowManager.hpp"
#include "DebugWindow.hpp"
#include "RlImGuiDemo.hpp"
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

  windows.push_back(std::make_shared<RlImGuiDemo>());

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
