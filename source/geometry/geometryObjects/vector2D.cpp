#include "point2D.h"
#include "vector2D.h"

Vector2D::Vector2D(double x, double y):
  Coord2D(x, y)
{

}

Vector2D operator+(const Vector2D& first, const Vector2D& second)
{
  return Vector2D{ first[0] + second[0], first[1] + second[1] };
}

Vector2D operator-(const Vector2D& first, const Vector2D& second)
{
  return Vector2D{ first[0] - second[0], first[1] - second[1] };
}

Vector2D operator*(const Vector2D& first, double multiplier)
{
  return Vector2D{ first[0] * multiplier, first[1] * multiplier };
}

Vector2D operator*(double multiplier, const Vector2D& second)
{
  return second * multiplier;
}




