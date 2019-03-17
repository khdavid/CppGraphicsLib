#include "rayIntersectionUtil.h"
#include "geometryUtils.h"
#include "geometryObjects/point.h"
#include "geometryObjects/matrix.h"

namespace
{
bool isInsideSphere(const Point3D& point, const Sphere& sphere)
{
  using namespace GeometryUtils;
  auto rVector = point - sphere.center;
  return sqr(rVector) <= sqr(sphere.radius);
}

bool isRayStartsBeforeSphereCenter(const Ray& ray, const Sphere& sphere)
{
  auto rVector = sphere.center - ray.point;
  return rVector * ray.direction >= 0;
}

bool isRayStartsBeforeSphere(const Ray& ray, const Sphere& sphere)
{
  return isRayStartsBeforeSphereCenter(ray, sphere) &&
    !isInsideSphere(ray.point, sphere);
}

bool isRayStartsAfterSphere(const Ray& ray, const Sphere& sphere)
{
  return !isRayStartsBeforeSphereCenter(ray, sphere) &&
    !isInsideSphere(ray.point, sphere);
}

std::optional<std::pair<Point3D, Point3D>> isLineHittingSphere(const Ray& ray, const Sphere& sphere)
{
  auto centerVec = sphere.center - ray.point;

  // we should solve the quadratic equation:
  // lenSqr(t * ray.direction - centerVec) = sqr(ball.radius);
  // lenSqr(ray.direction) * t^2 - 2 * dot(ray.direction, centerVec) * t + lenSqr(centerVec) - sqr(ball.radius) = 0;
  using namespace GeometryUtils;
  auto D = sqr(ray.direction * centerVec ) - sqr(ray.direction) * (sqr(centerVec) - sqr(sphere.radius));

  if (D < 0)
  {
    return std::nullopt;
  }
  auto t1 = ((ray.direction * centerVec) - sqrt(D)) / sqr(ray.direction);
  auto t2 = ((ray.direction * centerVec) + sqrt(D)) / sqr(ray.direction);

  auto firstIntersection = ray.point + t1 * ray.direction;
  auto secondIntersection = ray.point + t2 * ray.direction;
  
  return std::pair<Point3D, Point3D>{firstIntersection, secondIntersection};
}


}//end of unnamed namespace

namespace RayIntersectionUtil
{
std::optional<Point3D> isRayHittingSphere(const Ray& ray, const Sphere& sphere)
{
  if (isRayStartsAfterSphere(ray, sphere))
  {
    return std::nullopt;
  }

  Point3D secondIntersection;
  auto intersectionPoints = isLineHittingSphere(ray, sphere);
  if (intersectionPoints)
  {
    if (isInsideSphere(ray.point, sphere))
    {
      return intersectionPoints->second;
    }
    return intersectionPoints->first;
  }

  return std::nullopt;
}

Ray getPickRay(const Point3D& coords, const Matrix4D& transform)
{
  auto point = Point3D(coords[0], coords[1], 0);
  auto direction = GeometryUtils::AXIS_Z;

  Ray result;
  result.point = transform * point;
  result.direction = transform * direction;
  return result;
}
}//end of RayIntersectionUtil namespace
