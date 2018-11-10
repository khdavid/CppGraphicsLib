#include "triangle2D.h"

Triangle2D::Triangle2D(
  const Point2D& first,
  const Point2D& second,
  const Point2D& third):
  IndexAccessor({first, second, third})
{

}

