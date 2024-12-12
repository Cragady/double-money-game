#ifndef DMG_RAYGUI_MAIN_CAMERA_HPP_
#define DMG_RAYGUI_MAIN_CAMERA_HPP_

#include "DMG/core/GameState.hpp"
#include "DMG/core/IGui.hpp"

class MainCamera : public IGui {
 public:
  MainCamera();

  void GuiSetup() override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  void BeginCamera(const GameStateUPtr &);
  void RenderCamera(const GameStateUPtr &);
  void EndCamera(const GameStateUPtr &);

  void MouseCapture(const GameStateUPtr &);
  void CorrectMouse(const GameStateUPtr &, Vector2, Vector2);

  Camera camera_ = {0};
  bool capture_cursor_ = false;
};

#endif
