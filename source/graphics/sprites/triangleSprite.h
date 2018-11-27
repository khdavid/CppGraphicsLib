#pragma once

#include <glew.h>
#include <geometryObjects/triangle2D.h>

class TriangleSprite
{
public:
  TriangleSprite(Triangle2D triangle);
  ~TriangleSprite();
  void draw(int x, int y);

private:
  Triangle2D triangle_;
  std::array<float, 6> vertexData_;
  GLuint vboId_ = 0;
};

