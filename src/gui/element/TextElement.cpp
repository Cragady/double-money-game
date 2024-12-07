#include "TextElement.hpp"

// Example:
// ImGui::Text("");

TextElement::TextElement() : TextElement("") {};
TextElement::TextElement(const char *text, ImGuiWindowFlags flags) {
  text_ = text;
  flags_ = flags;
};
TextElement::~TextElement(){};

void TextElement::Setup() {};
void TextElement::Shutdown() {};
void TextElement::Update() {};
void TextElement::BeginRender() {};
void TextElement::Render() {};
void TextElement::EndRender() {};
void TextElement::FullRender() {
  if (!open_) return;
  if (ImGui::Begin(name_.c_str(), &open_, flags_)) {
    ImGui::Text("%s", text_.c_str());
  }
  ImGui::End();

};
