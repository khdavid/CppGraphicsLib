#pragma once
#include "coord2D.h"

class Point2D;

class Vector2D : public Coord2D
{
public:
  explicit Vector2D() = default;
  explicit Vector2D(double x, double y);
 };

Vector2D operator+(const Vector2D& first, const Vector2D& second);
Vector2D operator-(const Vector2D& first, const Vector2D& second);
Vector2D operator*(const Vector2D& first, double multiplier);
Vector2D operator*(double multiplier, const Vector2D& second);
