#pragma once

#include <type_traits>

#include "vector.h"
#include "indexAccessor.h"


template <size_t n>
struct Point : IndexAccessor<double, n>
{
  static constexpr GeomEntityType geom_type = GeomEntityType::Point;
  using IndexAccessor<double, n>::IndexAccessor;
};

struct Point2D : public Point<2>
{
  using Point<2>::Point;
};

struct Point3D : public Point<3>
{
  using Point<3>::Point;
};
