#pragma once

#include "geometryObjects/point.h"
#include "listeners/inputEventListener.h"
#include "tool.h"

class GLSLProgramRayTracing;
class InputEventObservable;
class Model;

class ObjectsMovingTool : public Tool
{
public:  
  ObjectsMovingTool(
    GLSLProgramRayTracing& rayTracingProgram, 
    InputEventObservable& inputEventObservable,
    Model& model);
  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;

private:
  Point2D mousePoint_;
  Model& model_;
};

