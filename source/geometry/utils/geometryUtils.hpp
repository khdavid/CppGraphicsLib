#pragma once

namespace GeometryUtils
{
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

}