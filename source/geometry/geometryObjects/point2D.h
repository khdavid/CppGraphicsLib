#pragma once
#include <array>

#include "vector2D.h"
#include "coord2D.h"
class Vector2D;

class Point2D : public Coord2D
{
public:
  Point2D() = default;
  Point2D(double x, double y);
};

Point2D operator+(const Point2D& first, const Vector2D& second);
Point2D operator-(const Point2D& first, const Vector2D& second);
Vector2D operator-(const Point2D& first, const Point2D& second);



