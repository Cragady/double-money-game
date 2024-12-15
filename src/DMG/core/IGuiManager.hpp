#ifndef DMG_CORE_I_GUI_MANAGER_HPP_
#define DMG_CORE_I_GUI_MANAGER_HPP_

#include <memory>
#include <vector>

#include "DMG/core/GameState.hpp"
#include "DMG/core/IGui.hpp"

class IGuiManager {
 public:
  virtual void Setup(const GameStateUPtr &, bool) = 0;
  virtual void Update(const GameStateUPtr &) = 0;
  virtual void Shutdown(const GameStateUPtr &) = 0;

  std::vector<IGuiSPtr> guis_;
};

using IGuiManagerSPtr = std::shared_ptr<IGuiManager>;

#endif
