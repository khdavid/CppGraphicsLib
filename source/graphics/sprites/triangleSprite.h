#pragma once

#include <glew.h>
#include <geometryObjects/triangle2D.h>

class TriangleSprite
{
public:
  TriangleSprite(Triangle2D triangle);
  ~TriangleSprite();
  void render(int x, int y);

private:
  Triangle2D triangle_;
  GLuint vboPosition_ = 0;
  GLint vertexPositionAttr_ = 0;
  GLuint vboColor_ = 0;
  GLint vertexColorAttr_ = 0;
};

