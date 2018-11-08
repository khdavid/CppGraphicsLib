#pragma once
#include <array>

class Point2D
{
public:
  Point2D();
  Point2D(double x, double y);
  double& x();
  const double& x() const;
  double& y();
  const double& y() const;
  double& operator[](size_t index);
  const double& operator[](size_t index) const;
private:
  std::array<double, 2> arr_;
};

