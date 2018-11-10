#pragma once

#include <array>

#include "indexAccessor.h"

#include "Point2D.h"

class Triangle2D : public IndexAccessor<Point2D, 3>
{
public:
  Triangle2D(
    const Point2D& first,
    const Point2D& second,
    const Point2D& third);
};

