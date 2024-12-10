#ifndef DMG_GUI_STATS_WINDOW_HPP_
#define DMG_GUI_STATS_WINDOW_HPP_

#include "DMG/gui/IWindow.hpp"

class StatsWindow : public IWindow {
 public:
  StatsWindow();

  void GuiSetup() override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  float delta_time_ = 0.0f;
  double total_elapsed_time_ = 0.0f;
  int fps_ = 0;
};

#endif
