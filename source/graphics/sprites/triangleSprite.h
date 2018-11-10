#pragma once

#include <glew.h>
#include <geometryObjects/triangle2D.h>

class TriangleSprite
{
public:
  TriangleSprite(Triangle2D triangle);
  ~TriangleSprite();
  void draw();

private:
  Triangle2D triangle_;
  GLuint vboId_ = 0;
};

