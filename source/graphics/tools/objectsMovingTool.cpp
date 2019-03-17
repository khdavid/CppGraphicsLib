#include "GLSL/GLSLProgramRayTracing.h"
#include "observables/inputEventObservable.h"
#include "objectsMovingTool.h"
#include "model/model.h"
#include "utils/rayIntersectionUtil.h"
#include "utils/geometryUtils.h"


ObjectsMovingTool::ObjectsMovingTool(
  GLSLProgramRayTracing& rayTracingProgram, 
  InputEventObservable& inputEventObservable,
  Model& model):
  Tool(rayTracingProgram, inputEventObservable),
  model_(model)
{
}

void ObjectsMovingTool::onMouseClick(int x, int y)
{
  mousePoint_ = Point3D(x, y, 0);
  auto ray = RayIntersectionUtil::getPickRay(mousePoint_, rayTracingProgram_.getGlobalToCamera());
  pickedSphere_ = pickHittingSphere_(ray);
}

void ObjectsMovingTool::onMouseMove(int x, int y)
{
  auto mousePoint = Point3D(x, y, 0);
  auto motion = mousePoint - mousePoint_;
  mousePoint_ = mousePoint;

  motion = rayTracingProgram_.getGlobalToCamera() * motion;
  if (pickedSphere_)
  {
    auto& center = (*pickedSphere_)->center;
    center = center + motion;
    rayTracingProgram_.render();
  }
}

void ObjectsMovingTool::onMouseRelease(int, int)
{
  pickedSphere_ = std::nullopt;
}

std::optional<Sphere*> ObjectsMovingTool::pickHittingSphere_(const Ray& ray) const
{
  auto minDistanceSqr = std::numeric_limits<double>::infinity();
  std::optional<Sphere*> sphere;
  
  for (auto& sphereObject : model_.getSphereObjects())
  {
    auto intersectionPoint = RayIntersectionUtil::isRayHittingSphere(ray, sphereObject->getSphere());
    if (intersectionPoint)
    {
      auto distSqr = GeometryUtils::distanceSqr(*intersectionPoint, ray.point);
      if (distSqr < minDistanceSqr)
      {
        minDistanceSqr = distSqr;
        sphere = &sphereObject->getSphere();
      }
    }
  }

  return sphere;
}
