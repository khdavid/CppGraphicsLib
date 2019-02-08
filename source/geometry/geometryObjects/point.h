#pragma once

#include <type_traits>

#include "vector.h"
#include "indexAccessor.h"


template <class T, size_t n>
struct Point : IndexAccessor<T, n>
{
  static constexpr GeomEntityType geom_type = GeomEntityType::Point;
  using IndexAccessor<double, n>::IndexAccessor;
};

struct Point2D : public Point<double, 2>
{
  using Point<double, 2>::Point;
};

struct Point3D : public Point<double, 3>
{
  using Point<double, 3>::Point;
};
