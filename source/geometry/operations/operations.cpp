#include "geometryObjects/vector.h"
#include "geometryObjects/point.h"
#include "operations.h"
#include "geometryObjects/matrix.h"

Vector2D operator-(const Point2D& first, const Point2D& second)
{
  return Vector2D{ first[0] - second[0], first[1] - second[1] };
}

Vector3D operator-(const Point3D& first, const Point3D& second)
{
  return Vector3D{ first[0] - second[0], first[1] - second[1], first[2] - second[2]};
}

Point3D operator*(const Matrix4D& transformation, const Point3D& point)
{
  auto point4D = Vector<double, 4>(point[0], point[1], point[2], 1);
  auto point4DTrans = transformation * point4D;
  return Point3D(point4DTrans[0], point4DTrans[1], point4DTrans[2]);
}

Vector3D operator*(const Matrix4D& transformation, const Vector3D& vector)
{
  auto vector4D = Vector<double, 4>(vector[0], vector[1], vector[2], 0);
  auto vector4DTrans = transformation * vector4D;
  return Vector3D(vector4DTrans[0], vector4DTrans[1], vector4DTrans[2]);
}
