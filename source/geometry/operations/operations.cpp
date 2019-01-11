#include "geometryObjects/vector.h"
#include "geometryObjects/point.h"
#include "operations.h"

//Vector2D operator+(const Vector2D& first, const Vector2D& second)
//{
//  return Vector2D{ first[0] + second[0], first[1] + second[1] };
//}
//
//Vector2D operator-(const Vector2D& first, const Vector2D& second)
//{
//  return Vector2D{ first[0] - second[0], first[1] - second[1] };
//}
//
//Vector2D operator*(const Vector2D& first, double multiplier)
//{
//  return Vector2D{ first[0] * multiplier, first[1] * multiplier };
//}
//
//Vector2D operator*(double multiplier, const Vector2D& second)
//{
//  return second * multiplier;
//}
//
//Vector2D operator/(const Vector2D& first, double divisor)
//{
//  return first * (1 / divisor);
//}
//
//Point2D operator+(const Point2D& first, const Vector2D& second)
//{
//  return Point2D{ first[0] + second[0], first[1] + second[1] };
//}
//
//Point2D operator-(const Point2D& first, const Vector2D& second)
//{
//  return Point2D{ first[0] - second[0], first[1] - second[1] };
//}
//
//Vector2D operator-(const Point2D& first, const Point2D& second)
//{
//  return Vector2D{ first[0] - second[0], first[1] - second[1] };
//}
//
//double operator*(const Vector2D& first, const Vector2D& second)
//{
//  return first[0] * second[0] + first[1] * second[1];
//}
//
//
void test()
{
  Vector2D aa;
  aa + aa;

}
