#include "DMG/gui/GuiObject.hpp"

GuiObject::GuiObject(Private) {};

GuiObject::GuiObject(glm::vec3 position, glm::vec3 scale, glm::vec3 size,
                     glm::quat rotation)
    : GuiObject(Private()) {
  position_ = position;
  scale_ = scale;
  og_scale_ = scale;
  size_ = size;
  og_size_ = size;
  rotation_ = rotation;
};

GuiObject::~GuiObject() {};

std::shared_ptr<GuiObject> GuiObject::Create(glm::vec3 position,
                                             glm::vec3 scale, glm::vec3 size,
                                             glm::quat rotation) {
  return std::make_shared<GuiObject>(position, scale, size, rotation);
}

ICoreObjectSPtr GuiObject::SelectObject() {
  if (!selectable_) return nullptr;
  return shared_from_this();
}
