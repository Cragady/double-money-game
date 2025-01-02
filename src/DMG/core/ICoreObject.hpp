#ifndef DMG_CORE_I_CORE_OBJECT_HPP_
#define DMG_CORE_I_CORE_OBJECT_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>

class ICoreObject;
using ICoreObjectSPtr = std::shared_ptr<ICoreObject>;

class ICoreObject {
 public:
  virtual ICoreObjectSPtr SelectObject() = 0;

  bool updateable_ = false;
  std::string name_ = "ICoreObject Debug";
  glm::vec3 position_ = glm::vec3(0.0f);
  glm::quat rotation_ = glm::quat();
  glm::vec3 scale_ = glm::vec3(1.0f);
  glm::vec3 og_scale_ = glm::vec3(1.0f);
  glm::vec3 size_ = glm::vec3(1.0f);
  glm::vec3 og_size_ = glm::vec3(1.0f);
  bool selectable_ = false;
};

#endif
