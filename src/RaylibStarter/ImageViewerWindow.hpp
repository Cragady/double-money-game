#ifndef IMAGE_VIEWER_WINDOW_HPP
#define IMAGE_VIEWER_WINDOW_HPP

#include "DocumentWindow.hpp"

class ImageViewerWindow : public DocumentWindow {
public:
  void Setup() override;
  void Show() override;
  void Update() override;
  void Shutdown() override;
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
