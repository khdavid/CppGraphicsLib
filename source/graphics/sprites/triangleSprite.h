#pragma once

#include <geometryObjects/triangle2D.h>

class TriangleSprite
{
public:
  TriangleSprite(Triangle2D triangle);

private:
  Triangle2D triangle_;
};

