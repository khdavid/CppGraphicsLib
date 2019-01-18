#pragma once

enum class GeomEntityType
{
  Point,
  Vector,
  Matrix
};

template <class T, class K = T>
using enable_if_vector_t = std::enable_if_t<T::geom_type == GeomEntityType::Vector, K>;

template <class T, class K = T>
using enable_if_matrix_t = std::enable_if_t<T::geom_type == GeomEntityType::Matrix, K>;

template <class T, class K = T>
using enable_if_matrix_or_vector_t = std::enable_if_t<(
  T::geom_type == GeomEntityType::Matrix ||
  T::geom_type == GeomEntityType::Vector), K>;
