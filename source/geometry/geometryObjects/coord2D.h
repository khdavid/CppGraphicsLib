#pragma once

#include <array>

#include "indexAccessor.h"

class Coord2D : public IndexAccessor<double, 2>
{
public:
  Coord2D(double x, double y);
  virtual ~Coord2D() = default;

  double& x();
  const double& x() const;
  double& y();
  const double& y() const;
};

