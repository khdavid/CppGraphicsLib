#pragma once
#include <type_traits>
#include "geometryObjects/indexAccessor.h"

struct Vector2D;
struct Vector3D;
struct Point2D;
struct Point3D;

template <class T, class K = T>
using enable_if_vector_t = std::enable_if_t<T::geom_type == GeomEntityType::Vector, K>;



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

#include "operations.hpp"



