#pragma once

#include <array>

template <class T, size_t n>
class Matrix : public std::array<std::array<T, n>, n>
{
public:
  template <class ...E>
  Matrix(const E&...args) : std::array<std::array<T, n>, n>{T(args)...}
  {

  }

};
