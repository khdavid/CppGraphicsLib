#pragma once

namespace
{
template <class T, size_t n>
Matrix<T, n - 1> adj(const Matrix<T, n>& m, size_t iExcl, size_t jExcl)
{
  static_assert(n > 1, "Dimension should be greater than 1");
  Matrix<T, n - 1> result;

  size_t iAdj = 0;
  for (auto i = 0; i < n; ++i)
  {
    if (i == iExcl) 
      continue;

    size_t jAdj = 0;
    for (auto j = 0; j < n; ++j)
    {
      if (j == jExcl) 
        continue;

      result[iAdj][jAdj] = m[i][j];
      ++jAdj;
    }
    ++iAdj;
  }
  return result;
}
}
namespace GeometryUtils
{
template<class T>
T det(const Matrix<T, 1>& m) 
{
  return m[0][0];
}

template <class T, size_t n>
T det(const Matrix<T, n>& m)
{

  T result = 0;
  for (size_t j = 0; j < n; j++)
  {
    auto sign = (j % 2 == 0) ? 1 : -1;
    result += sign * m[0][j] * det(adj(m, 0, j));
  }
  return result;
}

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