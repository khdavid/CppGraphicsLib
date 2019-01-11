#pragma once
#include <type_traits>

struct Vector2D;
struct Point2D;

template <class T>
std::enable_if_t<T::geom_type == GeomEntityType::Vector, T> operator+(const T& first, const T& second)
{
  T result = first;
  return result;
}



//Vector2D operator+(const Vector2D& first, const Vector2D& second);
//Vector2D operator-(const Vector2D& first, const Vector2D& second);
//Vector2D operator*(const Vector2D& first, double multiplier);
//Vector2D operator*(double multiplier, const Vector2D& second);
//Vector2D operator/(const Vector2D& first, double divisor);
//double operator*(const Vector2D& first, const Vector2D& second);
//Point2D operator+(const Point2D& first, const Vector2D& second);
//Point2D operator-(const Point2D& first, const Vector2D& second);
//Vector2D operator-(const Point2D& first, const Point2D& second);

