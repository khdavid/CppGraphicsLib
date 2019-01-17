#pragma once

#include <array>

#include <operations/operations.h>

template <class T, size_t n>
struct Matrix : std::array<std::array<T, n>, n>
{
  constexpr static size_t dim = n;
  constexpr static GeomEntityType geom_type = GeomEntityType::Matrix;
  template <class ...E>
  Matrix(const E&...args) : std::array<std::array<T, n>, n>{T(args)...}
  {

  }
};

struct Matrix2D : Matrix <double, 2>
{
  using Matrix<double, 2>::Matrix;
};

struct Matrix3D : Matrix <double, 3>
{
  using Matrix<double, 3>::Matrix;
};

struct Matrix4D : Matrix <double, 4>
{
  using Matrix<double, 4>::Matrix;
};


