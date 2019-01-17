#pragma once
#include <type_traits>
#include "geometryObjects/indexAccessor.h"

struct Vector2D;
struct Vector3D;
struct Point2D;
struct Point3D;


template <class T, class K>
enable_if_vector_t<T, K> operator+(const K& first, const T& second);

template <class T>
enable_if_vector_t<T> operator*(const T& first, double multiplier);

template <class T>
enable_if_vector_t<T> operator*(double multiplier, const T& second);

template <class T, class K>
std::enable_if_t<K::geom_type == GeomEntityType::Vector, T> operator-(T first, const K& second);

template <class T>
enable_if_vector_t<T> operator-(const T& vector);

template <class T>
enable_if_vector_t<T> operator/(const T& first, double divisor);

Vector2D operator-(const Point2D& first, const Point2D& second);
Vector3D operator-(const Point3D& first, const Point3D& second);

template <class T>
enable_if_matrix_t<T> operator+(const T& m1, const T& m2)
{
  T result = m1;
  for (size_t i = 0; i < m1.size(); ++i)
  {
    for (size_t j = 0; j < m2.size(); ++j)
    {
      res[i][j] += m2[i][j];
    }
  }
}

#include "operations.hpp"



