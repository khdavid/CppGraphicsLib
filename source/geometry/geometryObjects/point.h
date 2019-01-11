#pragma once

#include <type_traits>
#include "indexAccessor.h"


struct Point2D : public IndexAccessor<double, 2>
{
   static constexpr GeomEntityType geom_type = GeomEntityType::Point;

   explicit Point2D(double x, double y) : IndexAccessor({ x, y }) {}
   explicit Point2D() = default;
};

struct Point3D : public IndexAccessor<double, 3>
{
  static constexpr GeomEntityType geom_type = GeomEntityType::Point;

  explicit Point3D(double x, double y, double z) : IndexAccessor({ x, y, z }) {}
  explicit Point3D() = default;
};

