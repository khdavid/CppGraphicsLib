#pragma once

#include <type_traits>

#include "operations/operations.h"
#include "indexAccessor.h"

template <class T, size_t n>
struct Vector : IndexAccessor<T, n>
{
  static constexpr GeomEntityType geom_type = GeomEntityType::Vector;
  using IndexAccessor<T, n>::IndexAccessor;
};

struct Vector2D : public Vector<double, 2>
{
  using Vector<double, 2>::Vector;
};

struct Vector3D : public Vector<double, 3>
{
  using Vector<double, 3>::Vector;
};
