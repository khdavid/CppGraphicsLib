#pragma once

#include <type_traits>

#include "operations/operations.h"
#include "indexAccessor.h"

template <size_t n>
struct Vector : IndexAccessor<double, n>
{
  static constexpr GeomEntityType geom_type = GeomEntityType::Vector;
  using IndexAccessor<double, n>::IndexAccessor;
};

struct Vector2D : public Vector<2>
{
  using Vector<2>::Vector;
};

struct Vector3D : public Vector<3>
{
  using Vector<3>::Vector;
};
