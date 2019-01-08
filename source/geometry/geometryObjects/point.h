#pragma once

#include "indexAccessor.h"

struct Point2D : public IndexAccessor<double, 2>
{
  explicit Point2D(double x, double y) : IndexAccessor({ x, y }) {}
};

struct Point3D : public IndexAccessor<double, 3>
{
  explicit Point3D(double x, double y, double z) : IndexAccessor({ x, y, z }) {}
};

