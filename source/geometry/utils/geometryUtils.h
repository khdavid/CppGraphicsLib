#pragma once
#include <array>

#include "geometryObjects/matrix.h"
#include "geometryObjects/point.h"


namespace GeometryUtils
{
const auto AXIS_X = Vector3D(1, 0, 0);
const auto AXIS_Y = Vector3D(0, 1, 0);
const auto AXIS_Z = Vector3D(0, 0, 1);

Vector3D normalized(const Vector3D& vector);
Vector3D cross(const Vector3D& first, const Vector3D& second);
Matrix4D createIdentityMatrix4D();
Matrix3D createIdentityMatrix3D();
Matrix4D createAffineTransform(const Matrix3D& rotation, const Vector3D& shift = {});
Matrix3D createRotation(const Vector3D& direction, double angle);
Matrix4D createAffineRotation(const Vector3D& direction, const Point3D& point, double angle);
Matrix4D createAffineScaling(const Point3D& centerPoint, double scale);

template <class T>
double sqr(const T& element)
{
  return element * element;
}

template <class T>
double distanceSqr(const T& el1, const T& el2)
{
  auto diff = el1 - el2;
  return sqr(diff);
}

template <class T>
double distance(const T& el1, const T& el2)
{
  auto diff = el1 - el2;
  return sqrt(sqr(diff));
}


template <size_t n, class T>
std::array<float, n * n> convertToGL(const Matrix<T, n>& matrix)
{
  std::array<float, n * n > result;
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      result[i * n + j] = float(matrix[i][j]);
    }
  }
  return result;
}
}//end of namespace GeometryUtils

