template <class T, class K>
enable_if_vector_t<T, K> operator+(const K& first, const T& second)
{
  static_assert(K::dim == T::dim, "Dimensions are not the same");
  K result = first;
  for (int i = 0; i < result.size(); ++i)
  {
    result[i] += second[i];
  }
  return result;
}

template <class T>
enable_if_vector_t<T> operator*(const T& first, double multiplier)
{
  T result = first;
  for (int i = 0; i < result.size(); ++i)
  {
    result[i] *= multiplier;
  }
  return result;
}

template <class T>
enable_if_vector_t<T> operator*(double multiplier, const T& second)
{
  return second * multiplier;
}

template <class T, class K>
std::enable_if_t<K::geom_type == GeomEntityType::Vector, T> operator-(T first, const K& second)
{
  return first + (-1 * second);
}

template <class T>
enable_if_vector_t<T> operator-(const T& vector)
{
  return -1 * vector;
}

template <class T>
enable_if_vector_t<T> operator/(const T& first, double divisor)
{
  return first * (1 / divisor);
}
