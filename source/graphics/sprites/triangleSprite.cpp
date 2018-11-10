#include <array>
#include "triangleSprite.h"


TriangleSprite::TriangleSprite(Triangle2D triangle):
  triangle_(triangle)
{
  glGenBuffers(1, &vboId_);
  std::array<float, 6> vertexData;
  vertexData[0] = triangle[0].x();
  vertexData[1] = triangle[0].y();

  vertexData[2] = triangle[1].x();
  vertexData[3] = triangle[1].y();

  vertexData[4] = triangle[2].x();
  vertexData[5] = triangle[2].y();

  glBindBuffer(GL_ARRAY_BUFFER, vboId_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData.data(), GL_STATIC_DRAW);

}

void TriangleSprite::draw()
{

}