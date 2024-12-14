#ifndef IMAGE_VIEWER_WINDOW_HPP
#define IMAGE_VIEWER_WINDOW_HPP

#include "DMG/gui/IWindow.hpp"

class ImageViewerWindow : public IWindow {
 public:
  ImageViewerWindow();
  ~ImageViewerWindow();

  void GuiSetup(const GameStateUPtr &) override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;
  void UpdateRenderTexture();

  Texture ImageTexture;
  Camera2D Camera = {0};

  Vector2 LastMousePos = {0};
  Vector2 LastTarget = {0};
  bool Dragging = false;

  bool DirtyScene = false;

  enum class ToolMode {
    None,
    Move,
  };

  ToolMode CurrentToolMode = ToolMode::None;
};

#endif
