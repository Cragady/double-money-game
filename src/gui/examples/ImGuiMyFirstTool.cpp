#include "ImGuiMyFirstTool.hpp"
#include <cmath>

ImGuiMyFirstTool::ImGuiMyFirstTool() {
  name_ = "My First Tool";
}

void ImGuiMyFirstTool::Setup() {};
void ImGuiMyFirstTool::Shutdown() {};
void ImGuiMyFirstTool::Update(const GameStateUPtr &state) {};
void ImGuiMyFirstTool::BeginRender(const GameStateUPtr &state) {};
void ImGuiMyFirstTool::Render(const GameStateUPtr &state) {};
void ImGuiMyFirstTool::EndRender(const GameStateUPtr &state) {};
void ImGuiMyFirstTool::FullRender(const GameStateUPtr &state) {
  if (!open_) return;


  ImGui::Begin("My First Tool", &open_,
               ImGuiWindowFlags_NoBackground);
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
      }
      if (ImGui::MenuItem("Close", "Ctrl+W")) {
        open_ = false;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  // Edit a color stored as 4 floats
  float my_color[4] = {1.0f, 0.25f, 0.5f, 1.0f};
  ImGui::ColorEdit4("Color", my_color);

  // Generate samples and plot them
  float samples[100];
  for (int n = 0; n < 100; n++)
    samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
  ImGui::PlotLines("Samples", samples, 100);

  // Display contents in a scrolling region
  ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
  ImGui::BeginChild("Scrolling");
  for (int n = 0; n < 50; n++)
    ImGui::Text("%04d: Some text", n);
  ImGui::EndChild();
  ImGui::End();
};
