#pragma once

#include <array>

#include "indexAccessor.h"

#include "point.h"

struct Triangle2D : public IndexAccessor<Point2D, 3>
{
  Triangle2D(
    const Point2D& first,
    const Point2D& second,
    const Point2D& third) :
    IndexAccessor({ first, second, third })
  {
  }
};

struct Triangle3D : public IndexAccessor<Point3D, 3>
{
  Triangle3D(
    const Point3D& first,
    const Point3D& second,
    const Point3D& third) :
    IndexAccessor({ first, second, third })
  {
  }
};
