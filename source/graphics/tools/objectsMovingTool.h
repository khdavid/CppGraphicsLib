#pragma once

#include <optional>
#include "geometryObjects/point.h"
#include "listeners/inputEventListener.h"
#include "tool.h"

class GLSLProgramRayTracing;
class InputEventObservable;
class Model;
struct Ray;
struct Sphere;

class ObjectsMovingTool : public Tool
{
public:  
  using Tool::Tool;
  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseRelease(int x, int y) override;

private:
  std::optional<Sphere*> pickHittingSphere_(const Ray& ray) const;
  
  Point3D mousePoint_;
  std::optional<Sphere*> pickedSphere_;
};

