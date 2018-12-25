#include <array>
#include "triangleSprite.h"


TriangleSprite::TriangleSprite(Triangle2D triangle):
  triangle_(triangle)
{
  std::array<float, 6> vertexData;

  vertexData[0] = triangle[0].x();
  vertexData[1] = triangle[0].y();

  vertexData[2] = triangle[1].x();
  vertexData[3] = triangle[1].y();

  vertexData[4] = triangle[2].x();
  vertexData[5] = triangle[2].y();

  // Enable alpha
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glGenBuffers(1, &vboPosition_);
  glBindBuffer(GL_ARRAY_BUFFER, vboPosition_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData.data(), GL_STATIC_DRAW);

  const char* vertexPositionName = "vertexPosition";
  vertexPositionAttr_ = glGetAttribLocation(1, vertexPositionName);

}

 TriangleSprite::~TriangleSprite()
{
  if (vboPosition_)
  {
    glDeleteBuffers(1, &vboPosition_);
  }
}


void TriangleSprite::render(int x, int y)
{
  const int cDim = 2;
  glVertexAttribPointer(
    vertexPositionAttr_, // attribute
    cDim,              // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0);                // offset of first element
  glDrawArrays(GL_TRIANGLES, 0, 3);
}


