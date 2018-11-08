#include "point2D.h"


Point2D::Point2D(double x, double y) :
arr_({x, y})
{
}

Point2D::Point2D() :
arr_({0, 0})
{
}

double& Point2D::x()
{
  return arr_[0];
}

const double& Point2D::x() const
{
  return arr_[0];
}

double& Point2D::y()
{
  return arr_[1];
}

const double& Point2D::y() const
{
  return arr_[1];
}

double& Point2D::operator[](size_t index)
{
  return arr_[index];
}

const double& Point2D::operator[](size_t index) const
{
  return arr_[index];
}




