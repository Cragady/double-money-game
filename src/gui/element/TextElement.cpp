#include "TextElement.hpp"

TextElement::TextElement() : TextElement("") {};
TextElement::TextElement(const char *text, ImGuiWindowFlags flags) {
  text_ = text;
  flags_ = flags;
};
TextElement::~TextElement(){};

void TextElement::GuiSetup() {}
void TextElement::DataSetup(const GameStateUPtr &state) {}
void TextElement::Setup(const GameStateUPtr &state) {};
void TextElement::Shutdown() {};
void TextElement::Update(const GameStateUPtr &state) {};
void TextElement::BeginRender(const GameStateUPtr &state) {};
void TextElement::Render(const GameStateUPtr &state) {};
void TextElement::EndRender(const GameStateUPtr &state) {};
void TextElement::FullRender(const GameStateUPtr &state) {
  if (!open_) return;
  if (ImGui::Begin(name_.c_str(), &open_, flags_)) {
    ImGui::Text("%s", text_.c_str());
  }
  ImGui::End();

};
