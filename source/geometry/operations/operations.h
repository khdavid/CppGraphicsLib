#pragma once
#include <type_traits>
#include "geometryObjects/indexAccessor.h"

struct Vector2D;
struct Vector3D;
struct Point2D;
struct Point3D;
struct Matrix4D;

template<class T, size_t n>
struct Vector;

template<class T,size_t n>
struct Matrix;

template <class T, class K>
enable_if_vector_t<T, K> operator+(const K& first, const T& second);

template <class T, class K>
enable_if_vector_t<T, K&> operator+=(K& first, const T& second);

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

template <class MatType, class VecType>
enable_if_vector_t<VecType> operator*(const MatType& m, const VecType& v);

Point3D operator*(const Matrix4D& transformation, const Point3D& point);
Vector3D operator*(const Matrix4D& transformation, const Vector3D& point);

#include "operations.hpp"



