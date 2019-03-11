#pragma once
#include <array>

#include "geomEntityType.h"

template <class T, size_t N>
class IndexAccessor : public std::array<T, N>
{
public:
  static constexpr size_t dim = N;
  template <class ...E>
  explicit IndexAccessor(const E&...args) : std::array<T,N>{T(args)...}
  {

  }
 };