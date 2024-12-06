#ifndef SCENE_VIEW_WINDOW
#define SCENE_VIEW_WINDOW

#include "IWindow.hpp"
#include <raylib.h>

class SceneViewWindow : public IWindow {
public:
  void Setup() override;
  void Shutdown() override;
  void Update() override;
  void BeginRender() override;
  void Render() override;
  void EndRender() override;
  void FullRender() override;

  Camera3D Camera = { 0 };
  Texture2D GridTexture = { 0 };
};

#endif
