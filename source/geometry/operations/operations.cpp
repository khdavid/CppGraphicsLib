#include "geometryObjects/vector.h"
#include "geometryObjects/point.h"
#include "operations.h"

Vector2D operator-(const Point2D& first, const Point2D& second)
{
  return Vector2D{ first[0] - second[0], first[1] - second[1] };
}

Vector3D operator-(const Point3D& first, const Point3D& second)
{
  return Vector3D{ first[0] - second[0], first[1] - second[1], first[2] - second[2]};
}