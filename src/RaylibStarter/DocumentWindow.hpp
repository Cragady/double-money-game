#ifndef DOCUMENT_WINDOW_HPP
#define DOCUMENT_WINDOW_HPP

#include <raylib.h>

class DocumentWindow {
public:
  bool Open = false;

  RenderTexture ViewTexture;

  virtual void Setup() = 0;
  virtual void Shutdown() = 0;
  virtual void Show() = 0;
  virtual void Update() = 0;

  bool Focused = false;

  Rectangle ContentRect = {0};
};

#endif
