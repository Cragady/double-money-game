#ifndef DEMO_HPP
#define DEMO_HPP

#include "ImageViewerWindow.hpp"
#include "SceneViewWindow.hpp"
class Demo {
public:
  Demo();
  ~Demo();
  void Prepare();
  void Update();
  void Render();
  void DoMainMenu();

  bool quit_ = false;
  bool imgui_demo_open_ = false;
  ImageViewerWindow image_viewer_;
  SceneViewWindow scene_view_;

};

#endif
