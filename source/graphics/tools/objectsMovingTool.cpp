#include "GLSL/GLSLProgramRayTracing.h"
#include "observables/inputEventObservable.h"
#include "objectsMovingTool.h"
#include "model/model.h"
#include "utils/rayIntersectionUtil.h"
#include "utils/geometryUtils.h"


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
  auto minDistance = std::numeric_limits<double>::infinity();
  std::optional<Sphere*> sphere;
  
  for (auto& sphereObject : model_.getSphereObjects())
  {
    auto intersectionPoints = RayIntersectionUtil::isLineHittingSphere(ray, sphereObject->getSphere());
    if (intersectionPoints)
    {
      auto dist = (intersectionPoints->first - ray.point) * ray.direction;
      if (dist < minDistance)
      {
        minDistance = dist;
        sphere = &sphereObject->getSphere();
      }
    }
  }

  return sphere;
}
