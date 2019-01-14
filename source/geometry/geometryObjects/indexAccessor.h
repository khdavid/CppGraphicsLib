#pragma once
#include <array>

enum class GeomEntityType
{
  Point,
  Vector
};

template <class T, size_t N>
class IndexAccessor : public std::array<T, N>
{
public:
  static constexpr size_t dim = N;
  template <class ...E>
  IndexAccessor(const E&...args) : std::array<T,N>{T(args)...}
  {

  }
 };