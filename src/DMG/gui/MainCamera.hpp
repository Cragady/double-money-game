#ifndef DMG_GUI_MAIN_CAMERA_HPP_
#define DMG_GUI_MAIN_CAMERA_HPP_

#include <common.h>

#include <vector>

#include "DMG/core/GameState.hpp"
#include "DMG/core/IGui.hpp"
#include "DMG/core/util/ColorShifting.hpp"
#include "DMG/gui/element/RayButton.hpp"

struct RaymarchLocs {
  unsigned int cam_pos, cam_dir, screen_center, check_1, check_2;
};

class MainCamera : public IGui {
 public:
  MainCamera();
  MainCamera(char *, char *, std::string = DMG_SHADER_PATH);

  void GuiSetup(const GameStateUPtr &) override;
  void DataSetup(const GameStateUPtr &) override;
  void Shutdown(const GameStateUPtr &) override;
  void Update(const GameStateUPtr &) override;
  void BeginRender(const GameStateUPtr &) override;
  void Render(const GameStateUPtr &) override;
  void EndRender(const GameStateUPtr &) override;
  void FullRender(const GameStateUPtr &) override;

  void DrawFloor(const GameStateUPtr &);

  void MouseCapture(const GameStateUPtr &);
  void CorrectMouse(const GameStateUPtr &, Vector2, Vector2);

  std::vector<IGuiSPtr> guis_;
  bool ready_ = false;
  Shader shader_;
  Shader shader_raymarch_;
  RaymarchLocs march_locs_ = {0};
  ColorShifting color_shifting_;
  CameraSPtr main_camera_ = nullptr;
  float cam_dist_ = 0.0f;
  bool capture_cursor_ = false;
  float render_color_[3];
  std::string fs_file_name_ = "fs-basic-color.glsl";
  std::string vs_file_name_ = "vs-basic-color.glsl";
  std::string shader_path_ = DMG_SHADER_PATH;
};

using MainCameraSPtr = std::shared_ptr<MainCamera>;

#endif
