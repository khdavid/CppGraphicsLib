#pragma once
template <class T, size_t N>

class IndexAccessor
{
public:
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

private:
  std::array<T, N> arr_;
};