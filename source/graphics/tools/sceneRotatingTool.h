#pragma once

#include "listeners/inputEventListener.h"
#include "geometryObjects/point.h"

class GLSLProgramRayTracing;
class InputEventObservable;

class SceneRotatingTool : public InputEventListener
{
public:
  SceneRotatingTool(GLSLProgramRayTracing& rayTracingProgram, InputEventObservable& inputEventObservable);
  ~SceneRotatingTool();
  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseScrolling(int velocity) override;


private:
  GLSLProgramRayTracing& rayTracingProgram_;
  Point2D mousePoint_;
  InputEventObservable& inputEventObservable_;
  double scale_ = 1.0;
};

