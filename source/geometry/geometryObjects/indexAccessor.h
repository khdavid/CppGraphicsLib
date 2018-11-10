#pragma once
template <class T, size_t N>

class IndexAccessor
{
public:
  IndexAccessor(std::array<T, N> arr) :
    arr_(arr)
  {

  }
  double& operator[](size_t index)
  {
    return arr_[index];
  }
  const double& operator[](size_t index) const
  {
    return arr_[index];
  }

private:
  std::array<T, N> arr_;
};