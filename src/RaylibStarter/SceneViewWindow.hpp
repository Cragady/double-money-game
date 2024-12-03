#ifndef SCENE_VIEW_WINDOW
#define SCENE_VIEW_WINDOW

#include "DocumentWindow.hpp"
#include <raylib.h>

class SceneViewWindow : public DocumentWindow {
public:
  void Setup() override;
  void Shutdown() override;
  void Show() override;
  void Update() override;

  Camera3D Camera = { 0 };
  Texture2D GridTexture = { 0 };
};

#endif
