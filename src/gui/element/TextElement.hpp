#ifndef DMG_GUI_ELEMENT_TEXT_ELEMENT_HPP_
#define DMG_GUI_ELEMENT_TEXT_ELEMENT_HPP_

#include "IWindow.hpp"
#include "imgui.h"
#include <string>

template <typename T = void> class TextElement : public IWindow {
public:
  TextElement();
  TextElement(const char *text, const char *name = "Debug - TextElement",
              ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoNav |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoDecoration |
                                       ImGuiWindowFlags_NoTitleBar // |
              // ImGuiWindowFlags_NoMove,
  );
  ~TextElement();

  void GuiSetup() override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown() override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  std::string text_;
  T *data_ptr_ = nullptr;
};

#endif
