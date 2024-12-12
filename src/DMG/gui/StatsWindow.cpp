#include "DMG/gui/StatsWindow.hpp"

#include <raylib.h>

#include <cmath>

#include "imgui.h"

StatsWindow::StatsWindow() { name_ = "Stats Window"; }

void StatsWindow::DataSetup(const GameStateUPtr &state) {}
void StatsWindow::GuiSetup() {}
void StatsWindow::Shutdown() {};
void StatsWindow::Update(const GameStateUPtr &state) {
  delta_time_ = state->delta_time_;
  total_elapsed_time_ = state->total_elapsed_time_;
  fps_ = state->fps_;
};
void StatsWindow::BeginRender(const GameStateUPtr &state) {
  render_ready_ = ImGui::Begin(name_.c_str(), &open_, flags_);
};
void StatsWindow::Render(const GameStateUPtr &state) {
  if (!open_) return;
  float samples[100];
  for (int n = 0; n < 100; n++)
    samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
  ImGui::PlotLines("Fun Thing", samples, 100);
  ImGui::SeparatorText("Time Stats");
  ImGui::Text("FPS: %i", fps_);
  ImGui::Text("Delta Time: %f", delta_time_);
  ImGui::Text("Total Elapsed Time: %lf", total_elapsed_time_);
  Vector2 mouse_pos = GetMousePosition();
  ImVec2 im_mouse_pos = ImGui::GetMousePos();
  ImGui::Text("Raylib Mouse Pos: x:%f y:%f", mouse_pos.x, mouse_pos.y);
  ImGui::Text("ImGui Mouse Pos: x:%f y:%f", im_mouse_pos.x, im_mouse_pos.y);
};
void StatsWindow::EndRender(const GameStateUPtr &state) { ImGui::End(); };

void StatsWindow::FullRender(const GameStateUPtr &state) {
  if (!open_) return;
  BeginRender(state);
  Render(state);
  EndRender(state);
}