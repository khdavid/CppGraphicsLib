#pragma once

#include "indexAccessor.h"

struct Vector2D : public IndexAccessor<double, 2>
{
  explicit Vector2D(double x, double y) : IndexAccessor({ x, y }) {}
};

struct Vector3D : public IndexAccessor<double, 3>
{
  explicit Vector3D(double x, double y, double z) : IndexAccessor({ x, y, z }) {}
};
