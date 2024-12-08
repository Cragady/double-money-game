#ifndef SCENE_VIEW_WINDOW
#define SCENE_VIEW_WINDOW

#include "IWindow.hpp"
#include <raylib.h>

class SceneViewWindow : public IWindow {
public:
  ~SceneViewWindow();

  void Setup() override;
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
