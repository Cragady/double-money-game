#include "WindowManager.hpp"
#include "DebugWindow.hpp"
#include "GameState.hpp"
#include "ImGuiMyFirstTool.hpp"
#include "RlImGuiDemo.hpp"
#include <memory>

WindowManager::WindowManager() {
  debug_window_ = std::make_shared<DebugWindow>();

  if (include_debug_window_ && !debug_window_attached_) {
    windows_.push_back(debug_window_);
    debug_window_attached_ = true;

    std::shared_ptr<ImGuiMyFirstTool> my_tool =
        std::make_shared<ImGuiMyFirstTool>();
    debug_window_->CopyBoolPtrTwo(
        Dw_CbpArgs{.name = my_tool->name_, .bool_ptr = &(my_tool->open_)});
    windows_.push_back(my_tool);

    std::shared_ptr<RlImGuiDemo> rlimgui_demo = std::make_shared<RlImGuiDemo>();
    debug_window_->RlimguiCtrl(Dw_CbpArgs{.name = rlimgui_demo->name_,
                                          .bool_ptr = &(rlimgui_demo->open_)});
    windows_.push_back(rlimgui_demo);
  }
}

WindowManager::~WindowManager() {}

void WindowManager::Shutdown() {
  for (const IWindowPtr &window : windows_) {
    window->Shutdown();
  }
}

void WindowManager::Setup() {
  for (const IWindowPtr &window : windows_) {
    window->Setup();
  }
}

void WindowManager::Update(const GameStateUPtr &state) {
  for (const IWindowPtr &window : windows_) {
    window->Update(state);
    window->FullRender(state);
  }
}
