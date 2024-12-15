#include "DMG/gui/scene-creator.hpp"

#include <functional>
#include <memory>

#include "DMG/core/GameState.hpp"
#include "DMG/core/events/event-functions.hpp"
#include "DMG/gui/DebugWindow.hpp"
#include "DMG/gui/Scene.hpp"
#include "DMG/gui/StatsWindow.hpp"
#include "DMG/gui/imgui/element/Button.hpp"
// #include "DMG/gui/element/ShaderButton.hpp"
#include "DMG/gui/imgui/element/TextElement.hpp"
#include "DMG/gui/imgui/examples/ImGuiMyFirstTool.hpp"
#include "DMG/raygui/RayButton.hpp"
#include "DMG/vendor/RlImGuiDemo.hpp"

namespace scenecreator {

SceneCreator::SceneCreator(MainCameraSPtr scene_camera,
                           DebugWindowSPtr debug_window) {
  debug_window_ = debug_window;
  scene_camera_ = scene_camera;
};

SceneSPtr SceneCreator::Setup(const GameStateUPtr &state) {
  if (debug_window_ == nullptr) return nullptr;
  created_scene_.reset();
  // We assign the default camera, or a defined camera in the individual calls
  created_scene_ = std::make_shared<Scene>(nullptr, debug_window_);
  switch (state->current_page_) {
    case GamePageFlags_Debug:
      CreateDebugScene(state);
    default:
      break;
  }
  created_scene_->PassScenesToCamera();
  return created_scene_;
};

void SceneCreator::CreateCommonElements(const GameStateUPtr &state,
                                        unsigned long *current_element) {
  if (!debug_window_ || !scene_camera_) return;

  std::function<void()> lambda = [this]() {
    AddWindowToCollections(debug_window_);
  };
  AddAndCreate(lambda, current_element, true);

  lambda = [this]() {
    std::shared_ptr<ImGuiMyFirstTool> my_tool =
        std::make_shared<ImGuiMyFirstTool>();
    AddWindowToCollections(my_tool);
  };
  AddAndCreate(lambda, current_element);

  ImGuiMyFirstTool *my_tool =
      (ImGuiMyFirstTool *)created_scene_->guis_[*current_element].get();

  debug_window_->CopyBoolPtrTwo(
      Dw_CbpArgs {.name = my_tool->name_, .bool_ptr = &(my_tool->open_)});

  lambda = [this]() {
    std::shared_ptr<RlImGuiDemo> rlimgui_demo = std::make_shared<RlImGuiDemo>();
    AddWindowToCollections(rlimgui_demo);
  };
  AddAndCreate(lambda, current_element);

  RlImGuiDemo *rlimgui_demo =
      (RlImGuiDemo *)created_scene_->guis_[*current_element].get();

  debug_window_->RlimguiCtrl(Dw_CbpArgs {.name = rlimgui_demo->name_,
                                         .bool_ptr = &(rlimgui_demo->open_)});

  lambda = [this]() {
    std::shared_ptr<StatsWindow> stats_window = std::make_shared<StatsWindow>();
    AddWindowToCollections(stats_window);
  };
  AddAndCreate(lambda, current_element);

  StatsWindow *stats_window =
      (StatsWindow *)created_scene_->guis_[*current_element].get();

  debug_window_->SetProgramFlag2(
      Dw_CbpArgs {.name = "Stats Window", .bool_ptr = &(stats_window->open_)});
};

void SceneCreator::CreateDebugScene(const GameStateUPtr &state) {
  if (debug_window_ == nullptr) return;
  unsigned long current_element = 0;

  created_scene_->scene_camera_ = scene_camera_;

  CreateCommonElements(state, &current_element);

  std::function<void()> lambda = [this]() {
    std::shared_ptr<Button> button = std::make_shared<Button>();
    button->open_ = true;
    AddWindowToCollections(button);
  };
  AddAndCreate(lambda, &current_element);
  Button *button = (Button *)created_scene_->guis_[current_element].get();
  button->ClickEvent = events::TestRandom;

  lambda = [this]() {
    std::shared_ptr<TextElement<void>> test_text =
        std::make_shared<TextElement<void>>("Hello, World!");
    test_text->open_ = true;
    AddWindowToCollections(test_text);
  };
  AddAndCreate(lambda, &current_element);

  lambda = [this]() {
    std::shared_ptr<TextElement<long double>> current_money =
        std::make_shared<TextElement<long double>>("Hello, World!",
                                                   "Debug - Current Money");
    current_money->open_ = true;
    AddWindowToCollections(current_money);
  };
  AddAndCreate(lambda, &current_element);
  TextElement<long double> *current_money =
      (TextElement<long double> *)created_scene_->guis_[current_element].get();

  current_money->data_ptr_ = &(state->current_money_);

  lambda = [this]() {
    std::shared_ptr<Button> add_money =
        std::make_shared<Button>("Debug - Add Money", "Add Money");
    add_money->open_ = true;
    AddWindowToCollections(add_money);
  };
  AddAndCreate(lambda, &current_element);
  Button *add_money = (Button *)created_scene_->guis_[current_element].get();
  add_money->ClickEvent = events::AddMoneyEvent;

  lambda = [this]() {
    std::shared_ptr<RayButton> debug_3D_button = std::make_shared<RayButton>();
    debug_3D_button->open_ = true;
    debug_3D_button->color_shifting_.shift_speed_ = 40;
    debug_3D_button->position_ = {2.0f, 6.6f, -5.0f};
    AddWindowToCollections(debug_3D_button);
  };
  AddAndCreate(lambda, &current_element);

  RayButton *debug_3D_button =
      (RayButton *)created_scene_->guis_[current_element].get();
  debug_3D_button->ClickEvent = events::TestEvent;

  // lambda = [this]() {
  //   std::shared_ptr<ShaderButton> shader_button =
  //       std::make_shared<ShaderButton>();
  //   AddWindowToCollections(shader_button);
  // };
  // AddAndCreate(lambda, &current_element);
};

void SceneCreator::AddWindowToCollections(IGuiSPtr scene_element,
                                          bool add_to_scene) {
  if (scene_element && add_to_scene)
    created_scene_->guis_.push_back(scene_element);
};

void SceneCreator::AddAndCreate(std::function<void()> &func,
                                unsigned long *current_element,
                                bool first_element) {
  if (!first_element) {
    (*current_element)++;
  }
  if (gui_setup_) return;
  func();
}

} // namespace scenecreator
