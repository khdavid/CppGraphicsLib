#include "coord2D.h"
Coord2D::Coord2D(double x, double y) :
  arr_({ x, y })
{
}

double& Coord2D::x()
{
  return arr_[0];
}

const double& Coord2D::x() const
{
  return arr_[0];
}

double& Coord2D::y()
{
  return arr_[1];
}

const double& Coord2D::y() const
{
  return arr_[1];
}

double& Coord2D::operator[](size_t index)
{
  return arr_[index];
}

const double& Coord2D::operator[](size_t index) const
{
  return arr_[index];
}


