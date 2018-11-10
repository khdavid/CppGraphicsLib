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
  glBindBuffer(GL_ARRAY_BUFFER, 0);

}

TriangleSprite::~TriangleSprite()
{
  if (vboId_)
  {
    glDeleteBuffers(1, &vboId_);
  }
}


void TriangleSprite::draw()
{
  glBindBuffer(GL_ARRAY_BUFFER, vboId_);
  {
    glEnableVertexAttribArray(0);
    {
      const int cDim = 2;
      glVertexAttribPointer(0, cDim, GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 6);
    } 
    glDisableVertexAttribArray(0);
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);

}