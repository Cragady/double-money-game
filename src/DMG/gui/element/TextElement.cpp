#include "DMG/gui/element/TextElement.hpp"
// #include <type_traits>

template <typename T> TextElement<T>::TextElement() : TextElement<T>("Debug"){};
template <typename T>
TextElement<T>::TextElement(const char *text, const char *name, ImGuiWindowFlags flags) {
  text_ = text;
  flags_ = flags;
  name_ = name;
};

template <typename T> TextElement<T>::~TextElement(){};

template <typename T> void TextElement<T>::GuiSetup() {}
template <typename T>
void TextElement<T>::DataSetup(const GameStateUPtr &state) {}
template <typename T> void TextElement<T>::Shutdown() {};
template <typename T>
void TextElement<T>::Update(const GameStateUPtr &state) {
  // if (std::is_same<T, void>::value) {
  //   std::cout << "This too bb" << std::endl;
  // }
};
template <>
void TextElement<long double>::Update(const GameStateUPtr &state) {
  if (!data_ptr_) return;
  text_.clear();
  text_ = std::to_string(*data_ptr_);
};
template <typename T>
void TextElement<T>::BeginRender(const GameStateUPtr &state) {};
template <typename T>
void TextElement<T>::Render(const GameStateUPtr &state) {};
template <typename T>
void TextElement<T>::EndRender(const GameStateUPtr &state) {};
template <typename T>
void TextElement<T>::FullRender(const GameStateUPtr &state) {
  if (!open_)
    return;
  if (ImGui::Begin(name_.c_str(), &open_, flags_)) {
    ImGui::Text("%s", text_.c_str());
  }
  ImGui::End();
};


template class TextElement<void>;
template class TextElement<long double>;
