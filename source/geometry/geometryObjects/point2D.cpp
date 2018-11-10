#include "vector2D.h"
#include "point2D.h"

Point2D::Point2D(double x, double y) :
  Coord2D(x, y)
{
} 

Point2D operator+(const Point2D& first, const Vector2D& second)
{
  return Point2D{ first[0] + second[0], first[1] + second[1] };
}

Point2D operator-(const Point2D& first, const Vector2D& second)
{
  return Point2D{ first[0] - second[0], first[1] - second[1] };
}

Vector2D operator-(const Point2D& first, const Point2D& second)
{
  return Vector2D{ first[0] - second[0], first[1] - second[1] };
}





