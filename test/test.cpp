#include <DMG/Game.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Sanity Test", "[TEST_CASE]") { REQUIRE(true); }

TEST_CASE("Application Can Start - Will fail if Game fails", "[Game game]") {
  bool game_running_ctl = false;
  Game game = Game(&game_running_ctl, true);
  REQUIRE(true);
}
