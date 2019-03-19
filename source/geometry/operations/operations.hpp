template <class T, class K>
enable_if_vector_t<T, K> operator+(const K& first, const T& second)
{
  static_assert(K::dim == T::dim, "Dimensions are not the same");
  K result = first;
  for (size_t i = 0; i < result.size(); ++i)
  {
    result[i] += second[i];
  }
  return result;
}

template <class T, class K>
enable_if_vector_t<T, K&> operator+=(K& first, const T& second)
{
  first = first + second;
  return first;
}

template <class T>
enable_if_vector_t<T> operator*(const T& first, double multiplier)
{
  T result = first;
  for (size_t i = 0; i < result.size(); ++i)
  {
    result[i] *= multiplier;
  }
  return result;
}

template <class T>
enable_if_matrix_or_vector_t<T> operator*(double multiplier, const T& second)
{
  return second * multiplier;
}

template <class T, class K>
enable_if_matrix_or_vector_t<K, T> operator-(T first, const K& second)
{
  return first + (-1 * second);
}

template <class T>
enable_if_matrix_or_vector_t<T> operator-(const T& vector)
{
  return -1 * vector;
}

template <class T>
enable_if_matrix_or_vector_t<T> operator/(const T& first, double divisor)
{
  return first * (1 / divisor);
}

template <class T>
enable_if_matrix_t<T> operator+(const T& m1, const T& m2)
{
  T result = m1;
  for (size_t i = 0; i < m1.size(); ++i)
  {
    for (size_t j = 0; j < m2.size(); ++j)
    {
      result[i][j] += m2[i][j];
    }
  }
  return result;
}

template <class T>
enable_if_matrix_t<T> operator*(const T& m, double multiplier)
{
  T result = m;
  for (size_t i = 0; i < m.size(); ++i)
  {
    for (size_t j = 0; j < m.size(); ++j)
    {
      result[i][j] = m[i][j] * multiplier;
    }
  }
  return result;
}

template <class T>
enable_if_vector_t<T, double> operator*(const T& v1, const T& v2)
{
  double res = 0;
  for (size_t i = 0; i < v1.size(); ++i)
  {
    res += v1[i] * v2[i];
  }
  return res;
}

template <class T>
enable_if_matrix_t<T, double> cellOFMultiplier(const T& m1, const T& m2, size_t rowIdx, size_t columnIdx)
{
  double result = 0;
  for (size_t i = 0; i < m1.size(); ++i)
  {
    result += m1[rowIdx][i] * m2[i][columnIdx];
  }
  return result;
}

template <class T>
enable_if_matrix_t<T> operator*(const T& m1, const T& m2)
{
  T res;
  for (size_t i = 0; i < m1.size(); ++i)
  {
    for (size_t j = 0; j < m2.size(); ++j)
    {
      res[i][j] = cellOFMultiplier(m1, m2, i, j);
    }
  }
  return res;
}

template <class MatType, class VecType>
enable_if_vector_t<VecType> operator*(const MatType& m, const VecType& v)
{
  auto n = v.dim;
  VecType result;
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      result[i] += m[i][j] * v[j];
    }
  }
  return result;
}




