#include "rayIntersectionUtil.h"
#include "geometryUtils.h"

namespace
{
bool isInsideBall(const Point3D& point, const Sphere& sphere)
{
  using namespace GeometryUtils;
  auto rVector = point - sphere.center;
  return sqr(rVector) <= sqr(sphere.radius);
}

bool isRayStartsBeforeBallCenter(const Ray& ray, const Sphere& sphere)
{
  auto rVector = sphere.center - ray.point;
  return rVector * ray.direction >= 0;
}

bool isRayStartsBeforeBall(const Ray& ray, const Sphere& sphere)
{
  return isRayStartsBeforeBallCenter(ray, sphere) &&
    !isInsideBall(ray.point, sphere);
}

bool isRayStartsAfterBall(const Ray& ray, const Sphere& sphere)
{
  return !isRayStartsBeforeBallCenter(ray, sphere) &&
    !isInsideBall(ray.point, sphere);
}

std::optional<std::pair<Point3D, Point3D>> isLineHittingBall(const Ray& ray, const Sphere& ball)
{
  auto centerVec = ball.center - ray.point;

  // we should solve the quadratic equation:
  // lenSqr(t * ray.direction - centerVec) = sqr(ball.radius);
  // lenSqr(ray.direction) * t^2 - 2 * dot(ray.direction, centerVec) * t + lenSqr(centerVec) - sqr(ball.radius) = 0;
  using namespace GeometryUtils;
  auto D = sqr(ray.direction * centerVec ) - sqr(ray.direction) * (sqr(centerVec) - sqr(ball.radius));

  std::optional<std::pair<Point3D, Point3D>> result;
  if (D < 0)
  {
    return result;
  }
  auto t1 = ((ray.direction * centerVec) - sqrt(D)) / sqr(ray.direction);
  auto t2 = ((ray.direction * centerVec) + sqrt(D)) / sqr(ray.direction);

  auto firstIntersection = ray.point + t1 * ray.direction;
  auto secondIntersection = ray.point + t2 * ray.direction;
  
  return std::pair<Point3D, Point3D>{firstIntersection, secondIntersection};
}
//
//bool isRayHittingBall(in Ray ray, in Ball ball, out vec3 firstIntersection)
//{
//  if (isRayStartsAfterBall(ray, ball))
//  {
//    return false;
//  }
//
//  vec3 secondIntersection;
//  if (isLineHittingBall(ray, ball, firstIntersection, secondIntersection))
//  {
//    if (isInsideBall(ray.point, ball))
//    {
//      firstIntersection = secondIntersection;
//    }
//
//    return true;
//  }
//
//  return false;
//}

}//end of unnamed namespace

namespace RayIntersectionUtil
{
std::optional<Point3D> isIntersecting(const Sphere& /*sphere*/, const Ray& /*ray*/)
{
  return {};
}
}//end of RayIntersectionUtil namespace
