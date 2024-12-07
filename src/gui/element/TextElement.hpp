#ifndef DMG_GUI_ELEMENT_TEXT_ELEMENT_HPP_
#define DMG_GUI_ELEMENT_TEXT_ELEMENT_HPP_

#include "IWindow.hpp"
#include "imgui.h"
#include <string>

class TextElement : public IWindow {
public:
  TextElement();
  TextElement(const char *text,
              ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoNav |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoDecoration // |
              // ImGuiWindowFlags_NoMove,
  );
  ~TextElement();

  void Setup() override;
  void Shutdown() override;
  void Update() override;
  void BeginRender() override;
  void Render() override;
  void EndRender() override;
  void FullRender() override;

  std::string text_;
};

#endif
