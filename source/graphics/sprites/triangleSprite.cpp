#include <array>
#include "triangleSprite.h"


TriangleSprite::TriangleSprite(Triangle2D triangle):
  triangle_(triangle)
{
  vertexData_[0] = triangle[0].x();
  vertexData_[1] = triangle[0].y();

  vertexData_[2] = triangle[1].x();
  vertexData_[3] = triangle[1].y();

  vertexData_[4] = triangle[2].x();
  vertexData_[5] = triangle[2].y();

  glGenBuffers(1, &vboId_);
  glBindBuffer(GL_ARRAY_BUFFER, vboId_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData_), vertexData_.data(), GL_STATIC_DRAW);

}

 TriangleSprite::~TriangleSprite()
{
  if (vboId_)
  {
    glDeleteBuffers(1, &vboId_);
  }
}


void TriangleSprite::render(int x, int y)
{
  vertexData_[0] = float(x) / 320 - 1;
  vertexData_[1] = 1 - float(y) / 240;
  const char* name = "vertexPosition";
  auto attribute_coord2d = glGetAttribLocation(1, name);
  const int cDim = 2;

  glVertexAttribPointer(
    attribute_coord2d, // attribute
    cDim,              // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0);                // offset of first element
  glDrawArrays(GL_TRIANGLES, 0, 3);

}


