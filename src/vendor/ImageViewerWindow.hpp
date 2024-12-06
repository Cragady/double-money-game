#ifndef IMAGE_VIEWER_WINDOW_HPP
#define IMAGE_VIEWER_WINDOW_HPP

#include "IWindow.hpp"

class ImageViewerWindow : public IWindow {
public:
  void Setup() override;
  void Shutdown() override;
  void Update() override;
  void BeginRender() override;
  void Render() override;
  void EndRender() override;
  void FullRender() override;
  void UpdateRenderTexture();


	Texture ImageTexture;
	Camera2D Camera = { 0 };

	Vector2 LastMousePos = { 0 };
	Vector2 LastTarget = { 0 };
	bool Dragging = false;

	bool DirtyScene = false;

	enum class ToolMode
	{
		None,
		Move,
	};

	ToolMode CurrentToolMode = ToolMode::None;
};

#endif
