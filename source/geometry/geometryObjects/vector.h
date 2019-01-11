#pragma once

#include <type_traits>

#include "indexAccessor.h"

struct Vector2D : public IndexAccessor<double, 2>
{
  static constexpr GeomEntityType geom_type = GeomEntityType::Vector;

  explicit Vector2D(double x, double y) : IndexAccessor({ x, y }) {}
  explicit Vector2D() = default;
};

struct Vector3D : public IndexAccessor<double, 3>
{
  static constexpr GeomEntityType geom_type = GeomEntityType::Vector;

  explicit Vector3D(double x, double y, double z) : IndexAccessor({ x, y, z }) {}
  explicit Vector3D() = default;
};
