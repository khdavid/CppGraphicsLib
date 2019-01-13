#pragma once

#include <type_traits>

#include "operations/operations.h"
#include "indexAccessor.h"

template <size_t n>
struct Vector : IndexAccessor<double, n>
{
  static constexpr GeomEntityType geom_type = GeomEntityType::Vector;

  template <class ...E>
  Vector(E&&...args) : IndexAccessor({ std::forward<E>(args)... })
  {
  }
  
  Vector() = default;
};


struct Vector2D : public Vector<2>
{
  explicit Vector2D(double x, double y) : Vector({ x, y }) {}
  explicit Vector2D() = default;
};

struct Vector3D : public Vector<3>
{
  explicit Vector3D(double x, double y, double z) : Vector({ x, y, z }) {}
  explicit Vector3D() = default;
};
