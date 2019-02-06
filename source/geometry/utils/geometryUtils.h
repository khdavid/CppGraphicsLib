#pragma once
#include <array>

#include "geometryObjects/matrix.h"


namespace GeometryUtils
{
Matrix4D createIdentityMatrix4D();

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

