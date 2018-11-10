#pragma once
#include <array>

#include "operations/operations.h"
#include "coord2D.h"
#include "vector2D.h"
class Vector2D;

class Point2D : public Coord2D
{
public:
  Point2D() = default;
  Point2D(double x, double y);
};


