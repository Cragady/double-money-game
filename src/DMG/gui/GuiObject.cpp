#include "DMG/gui/GuiObject.hpp"

GuiObject::GuiObject(glm::vec3 position, glm::vec3 scale, glm::vec3 size,
                     glm::quat rotation) {
  position_ = position;
  scale_ = scale;
  size_ = size;
  rotation_ = rotation;
};

GuiObject::~GuiObject() {};

ICoreObject *GuiObject::SelectObject() {
  if (!selectable_) return nullptr;
  return this;
}
