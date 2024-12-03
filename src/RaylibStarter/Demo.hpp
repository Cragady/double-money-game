#ifndef DEMO_HPP
#define DEMO_HPP

#include "ImageViewerWindow.hpp"
#include "SceneViewWindow.hpp"
class Demo {
public:
  void Prepare();
  void Update();
  void Shutdown();
  void DoMainMenu();

  bool Quit = false;
  bool ImGuiDemoOpen = false;
  ImageViewerWindow ImageViewer;
  SceneViewWindow SceneView;
  int screenWidth = 1900;
  int screenHeight = 900;
  int targetFramerate = 144;

};

#endif
