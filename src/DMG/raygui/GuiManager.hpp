#ifndef DMG_RAYGUI_GUI_MANAGER_HPP_
#define DMG_RAYGUI_GUI_MANAGER_HPP_

#include <memory>
#include <vector>

#include "DMG/core/GameState.hpp"
#include "DMG/core/IGui.hpp"

class GuiManager {
 public:
  GuiManager();
  ~GuiManager();

  void Setup(const GameStateUPtr &, bool);
  void Update(const GameStateUPtr &);
  void Shutdown(const GameStateUPtr &);

  std::vector<IGuiPtr> guis_;
};

using GuiManagerSPtr = std::shared_ptr<GuiManager>;

#endif
