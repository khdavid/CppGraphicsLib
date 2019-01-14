#pragma once

#include <array>

template <class T, size_t n>
class Matrix
{
public:
  std::array<T,n>& operator[](size_t index)
  {
    return arr_[index];
  }
  const std::array<T,n>& operator[](size_t index) const
  {
    return arr_[index];
  }
private:
  std::array<std::array<T, n>, n> arr_{};
};
