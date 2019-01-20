#pragma once
#include <type_traits>
#include "geometryObjects/indexAccessor.h"

struct Vector2D;
struct Vector3D;
struct Point2D;
struct Point3D;

template<size_t n>
struct Vector;

template<class T,size_t n>
struct Matrix;

template <class T, class K>
enable_if_vector_t<T, K> operator+(const K& first, const T& second);

template <class T>
enable_if_vector_t<T> operator*(const T& first, double multiplier);

template <class T>
enable_if_matrix_t<T> operator*(const T& m, double multiplier);

template <class T>
enable_if_matrix_or_vector_t<T> operator*(double multiplier, const T& second);

template <class T, class K>
enable_if_matrix_or_vector_t<K,T> operator-(T first, const K& second);

template <class T>
enable_if_matrix_or_vector_t<T> operator-(const T& vector);

template <class T>
enable_if_matrix_or_vector_t<T> operator/(const T& first, double divisor);

Vector2D operator-(const Point2D& first, const Point2D& second);
Vector3D operator-(const Point3D& first, const Point3D& second);

template <class T>
enable_if_matrix_t<T> operator+(const T& m1, const T& m2);

template <class T>
enable_if_vector_t<T, double> operator*(const T& v1, const T& v2);

template <class T>
enable_if_matrix_t<T> operator*(const T& m1, const T& m2);

template <size_t n>
Vector<n> operator*(const Matrix<double, n>& m, const Vector<n>& v);

#include "operations.hpp"



