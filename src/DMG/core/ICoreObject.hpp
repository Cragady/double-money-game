#ifndef DMG_CORE_I_CORE_OBJECT_HPP_
#define DMG_CORE_I_CORE_OBJECT_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class ICoreObject {
 public:
  virtual ICoreObject *SelectObject() = 0;

  glm::vec3 position_ = glm::vec3(0.0f);
  glm::quat rotation_ = glm::quat();
  glm::vec3 scale_ = glm::vec3(1.0f);
  glm::vec3 size_ = glm::vec3(1.0f);
  bool selectable_ = false;
};

#endif
