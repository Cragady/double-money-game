#ifndef DMG_VENDOR_RL_IMGUI_DEMO_HPP_
#define DMG_VENDOR_RL_IMGUI_DEMO_HPP_

#include "ImageViewerWindow.hpp"
#include "SceneViewWindow.hpp"

class RlImGuiDemo : public IWindow {
public:
  RlImGuiDemo();
  ~RlImGuiDemo();

  void Setup() override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  void DoMainMenu();

  bool quit_ = false;
  bool imgui_demo_open_ = false;
  ImageViewerWindow image_viewer_;
  SceneViewWindow scene_view_;
};

#endif
