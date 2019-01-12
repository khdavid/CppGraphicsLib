#pragma once
#include <array>

enum class GeomEntityType
{
  Point,
  Vector
};

template <class T, size_t N>
class IndexAccessor
{
public:
  static constexpr size_t dim = N;
  IndexAccessor() = default;
  IndexAccessor(std::array<T, N> arr) :
    arr_(arr)
  {

  }
  T& operator[](size_t index)
  {
    return arr_[index];
  }
  const T& operator[](size_t index) const
  {
    return arr_[index];
  }
  constexpr size_t size() const
  {
    return arr_.size();
  }
private:
  std::array<T, N> arr_{}; //{} assures that arr_ is initialized with zeros
};