#include "geometryObjects/matrix.h"

#include "geometryUtils.h"

namespace GeometryUtils
{
Vector3D normalized(const Vector3D& vector)
{
  auto scalarProduct = vector * vector;
  return vector / sqrt(scalarProduct);
}

Vector3D cross(const Vector3D & first, const Vector3D & second)
{
  return Vector3D(
    first[1] * second[2] - first[2] * second[1],
    -first[0] * second[2] + first[2] * second[0],
    first[0] * second[1] - first[1] * second[0]);
}

Matrix4D createIdentityMatrix4D()
{
  Matrix4D result;
  for (int i = 0; i < 4; ++i)
  {
    result[i][i] = 1;
  }
  return result;
}

Matrix3D createIdentityMatrix3D()
{
  Matrix3D result;
  for (int i = 0; i < 3; ++i)
  {
    result[i][i] = 1;
  }
  return result;
}


Matrix4D createAffineTransform(const Matrix3D& rotation, const Vector3D& shift)
{
  Matrix4D result = createIdentityMatrix4D();
  for (size_t i = 0; i < 3; ++i)
  {
    for (size_t j = 0; j < 3; ++j)
    {
      result[i][j] = rotation[i][j];
    }
  }

  for (size_t i = 0; i < 3; ++i)
  {
    result[i][3] = shift[i];
  }

  return result;
}

Matrix3D createRotation(const Vector3D& direction, double angle)
{
  const auto u = normalized(direction);
  const auto a = angle;

  Matrix3D result = 
  {
    cos(a) + sqr(u[0]) * (1 - cos(a)),               u[0] * u[1] * (1 - cos(a)) - u[2] * sin(a),       u[0] * u[2] * (1 - cos(a)) + u[1] * sin(a),

    u[1] * u[0] * (1 - cos(a)) + u[2] * sin(a),      cos(a) + sqr(u[1]) * (1 - cos(a)),                u[1] * u[2] * (1 - cos(a)) - u[0] * sin(a),

    u[2] * u[0] * (1 - cos(a)) - u[1] * sin(a),      u[2] * u[1] * (1 - cos(a)) + u[0] * sin(a),       cos(a) + sqr(u[2]) * (1 - cos(a))
  };

  return result;
}

Matrix4D createAffineRotation(const Vector3D& direction, const Point3D& point, double angle)
{
  const auto u = normalized(direction);
  const Point3D origin;

  auto moveOriginToPoint = createAffineTransform(createIdentityMatrix3D(), point - origin);
  auto rotation = createRotation(u, angle);
  auto affineRotationAlongOrigin = createAffineTransform(rotation);
  auto movePointToOrigin = createAffineTransform(createIdentityMatrix3D(), origin - point);
  return moveOriginToPoint * affineRotationAlongOrigin * movePointToOrigin;
}

Matrix4D createAffineScaling(const Point3D& centerPoint, double scale)
{
  const Point3D origin;

  auto moveOriginToCenterPoint = createAffineTransform(createIdentityMatrix3D(), centerPoint - origin);
  auto scalingMatrix = createIdentityMatrix3D() * scale;
  auto affineScalingAlongOrigin = createAffineTransform(scalingMatrix);

  auto moveCenterPointToOrigin = createAffineTransform(createIdentityMatrix3D(), origin - centerPoint);
  return moveOriginToCenterPoint * affineScalingAlongOrigin * moveCenterPointToOrigin;
}


}// end of namespacde GeometryUtils
