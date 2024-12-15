#ifndef DMG_CORE_I_CORE_BASE_HPP_
#define DMG_CORE_I_CORE_BASE_HPP_

#include <memory>

class GameState;
using GameStateUPtr = std::unique_ptr<GameState>;

class ICoreBase {
 public:
  virtual void Setup(const GameStateUPtr &, bool = false) = 0;
  virtual void Update(const GameStateUPtr &) = 0;
  virtual void Shutdown(const GameStateUPtr &) = 0;
};

#endif
