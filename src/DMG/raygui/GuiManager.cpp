#include "DMG/raygui/GuiManager.hpp"

// #include <memory>

#include "DMG/core/GameState.hpp"
#include "DMG/core/IGui.hpp"
// #include "DMG/core/events/event-functions.hpp"
// #include "DMG/raygui/RayButton.hpp"

GuiManager::GuiManager() {};
GuiManager::~GuiManager() {};

// TODO: consider putting inside of camera
void GuiManager::Setup(const GameStateUPtr &state, bool gui_setup) {
  if (!gui_setup) {
    // std::shared_ptr<RayButton> button = std::make_shared<RayButton>();
    // button->open_ = true;
    // button->color_shifting_.shift_speed_ = 40;
    // button->ClickEvent = events::TestEvent;
    // guis_.push_back(button);
  }

  for (const IGuiPtr &gui : guis_) {
    if (!gui_setup) gui->GuiSetup();
    gui->DataSetup(state);
  }
};
void GuiManager::Update(const GameStateUPtr &state) {
  for (const IGuiPtr &gui : guis_) {
    gui->Update(state);
    gui->FullRender(state);
  }
};
void GuiManager::Shutdown() {
  for (const IGuiPtr &gui : guis_) {
    gui->Shutdown();
  }
};
