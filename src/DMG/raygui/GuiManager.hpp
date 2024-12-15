#ifndef DMG_RAYGUI_GUI_MANAGER_HPP_
#define DMG_RAYGUI_GUI_MANAGER_HPP_

#include <memory>

#include "DMG/core/GameState.hpp"
#include "DMG/core/IGuiManager.hpp"

class GuiManager : public IGuiManager {
 public:
  GuiManager();
  ~GuiManager();

  void Setup(const GameStateUPtr &, bool) override;
  void Update(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;
};

using GuiManagerSPtr = std::shared_ptr<GuiManager>;

#endif
