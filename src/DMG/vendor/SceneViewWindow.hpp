#ifndef SCENE_VIEW_WINDOW
#define SCENE_VIEW_WINDOW

#include "DMG/gui/IWindow.hpp"
#include <raylib.h>

class SceneViewWindow : public IWindow {
public:
  SceneViewWindow();
  ~SceneViewWindow();

  void GuiSetup() override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  Camera3D Camera = { 0 };
  Texture2D GridTexture = { 0 };
};

#endif
