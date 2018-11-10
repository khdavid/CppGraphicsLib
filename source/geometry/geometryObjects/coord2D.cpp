#include "coord2D.h"


Coord2D::Coord2D(double x, double y) :
  IndexAccessor({ x, y })
{
}

double& Coord2D::x()
{
  return (*this)[0];
}

const double& Coord2D::x() const
{
  return (*this)[0];
}

double& Coord2D::y()
{
  return (*this)[1];
}

const double& Coord2D::y() const
{
  return (*this)[1];
}




