#ifndef SCENE_VIEW_WINDOW
#define SCENE_VIEW_WINDOW

#include <raylib.h>

#include "DMG/gui/IWindow.hpp"

class SceneViewWindow : public IWindow {
 public:
  SceneViewWindow();
  ~SceneViewWindow();

  void GuiSetup(const GameStateUPtr &) override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  Camera3D Camera = {0};
  Texture2D GridTexture = {0};
};

#endif
