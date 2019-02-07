#include "geometryObjects/matrix.h"

#include "geometryUtils.h"

namespace GeometryUtils
{
Vector3D normalized(const Vector3D& vector)
{
  auto scalarProduct = vector * vector;
  return vector / sqrt(scalarProduct);
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

}// end of namespacde GeometryUtils
