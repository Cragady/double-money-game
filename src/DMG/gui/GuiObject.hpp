#ifndef DMG_GUI_GUI_OBJECT_HPP_
#define DMG_GUI_GUI_OBJECT_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>

#include "DMG/core/ICoreObject.hpp"

class GuiObject : public ICoreObject,
                  public std::enable_shared_from_this<GuiObject> {
 private:
  struct Private {
    explicit Private() = default;
  };

 public:
  GuiObject(Private);
  GuiObject(glm::vec3 position = glm::vec3(0.0f),
            glm::vec3 scale = glm::vec3(1.0f), glm::vec3 size = glm::vec3(1.0f),
            glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
  ~GuiObject();

  static std::shared_ptr<GuiObject> Create(
      glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f),
      glm::vec3 size = glm::vec3(1.0f),
      glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

  virtual ICoreObjectSPtr SelectObject() override;
};

#endif
