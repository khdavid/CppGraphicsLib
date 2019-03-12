#pragma once

#include "listeners/inputEventListener.h"
#include "geometryObjects/point.h"
#include "tool.h"

class GLSLProgramRayTracing;
class InputEventObservable;

class SceneRotatingTool : public Tool
{
public:
  using Tool::Tool;

  virtual void onKeyPress(SDL_Keycode keyCode) override;
  virtual void onMouseClickRight(int x, int y) override;
  virtual void onMouseMoveRight(int x, int y) override;
  virtual void onMouseScrolling(double velocity) override;
private:
  Point2D mousePoint_;
  double scale_ = 1.0;
};

