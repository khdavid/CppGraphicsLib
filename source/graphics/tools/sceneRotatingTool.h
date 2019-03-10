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

  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseScrolling(int velocity) override;
private:
  Point2D mousePoint_;
  double scale_ = 1.0;
};

