#pragma once

#include <array>

class Coord2D
{
public:
  Coord2D(double x, double y);
  virtual ~Coord2D() = default;


  double& x();
  const double& x() const;
  double& y();
  const double& y() const;
  double& operator[](size_t index);
  const double& operator[](size_t index) const;
private:
  std::array<double, 2> arr_ = {0, 0};
};

