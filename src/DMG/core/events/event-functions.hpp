#ifndef DMG_CORE_EVENTS_EVENT_FUNCTIONS_HPP_
#define DMG_CORE_EVENTS_EVENT_FUNCTIONS_HPP_

#include "DMG/core/GameState.hpp"

namespace events {
void TestEvent();
void TestEvent(const GameStateUPtr &);
void TestRandom(const GameStateUPtr &);
void AddMoneyEvent(const GameStateUPtr &);
} // namespace events

#endif
