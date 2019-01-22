#pragma once

#include <array>

#include "indexAccessor.h"

#include "point.h"

struct Triangle2D : public IndexAccessor<Point2D, 3>
{
  using IndexAccessor<Point2D, 3>::IndexAccessor;
};

struct Triangle3D : public IndexAccessor<Point3D, 3>
{
  using IndexAccessor<Point3D, 3>::IndexAccessor;
};

