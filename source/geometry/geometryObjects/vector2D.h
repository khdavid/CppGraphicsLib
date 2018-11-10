#pragma once
#include "operations/operations.h"
#include "coord2D.h"

class Point2D;

class Vector2D : public Coord2D
{
public:
  explicit Vector2D() = default;
  explicit Vector2D(double x, double y);
 };

