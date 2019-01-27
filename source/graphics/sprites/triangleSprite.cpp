#include "triangleSprite.h"
#include "triangleSprite.h"

namespace
{
  const char* cVertexPositionName = "vertexPosition";
  const char* cVertexColorName = "vertexColor";
}
void TriangleSprite::init(const std::vector<Vertex>& vertices)
{
  SpriteBase::init();
  numOfVertices_ = vertices.size();

  glGenBuffers(1, &vboVertices_);
  glBindBuffer(GL_ARRAY_BUFFER, vboVertices_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numOfVertices_, vertices.data(), GL_STATIC_DRAW);

  vertexPositionAttr_ = glGetAttribLocation(programId_, cVertexPositionName);
  vertexColorAttr_ = glGetAttribLocation(programId_, cVertexColorName);

  glEnableVertexAttribArray(vertexPositionAttr_);
  glEnableVertexAttribArray(vertexColorAttr_);

  glBindBuffer(GL_ARRAY_BUFFER, vboVertices_);
  const int cVertexPositionDim = 3;
  glVertexAttribPointer(
    vertexPositionAttr_, // attribute
    cVertexPositionDim,              // number of elements per vertex, here (x, y, z)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    sizeof(Vertex),                 // extra data between each position
    (const void *)offsetof(Vertex, position));                // offset of first element


  const int cVertexColorDim = 3;
  glVertexAttribPointer(
    vertexColorAttr_, // attribute
    cVertexColorDim,              // number of elements per vertex, here (x,y)
    GL_UNSIGNED_BYTE,          // the type of each element
    GL_FALSE,          // take our values as-is
    sizeof(Vertex),                 // no extra data between each position
    (const void *)offsetof(Vertex, material));                // offset of first element
}

void TriangleSprite::render(int x, int y)
{
  glDrawArrays(GL_TRIANGLES, 0, numOfVertices_);
}

TriangleSprite::~TriangleSprite()
{
  if (shaderProgram_)
  {
    glDeleteBuffers(1, &vboVertices_);
    glDisableVertexAttribArray(vertexColorAttr_);
    glDisableVertexAttribArray(vertexPositionAttr_);
  }
}

