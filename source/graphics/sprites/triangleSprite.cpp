#include <array>

#include "nodes/graphicsNode.h"
#include "triangleSprite.h"



TriangleSprite::TriangleSprite(Triangle2D triangle, GLuint programId):
  triangle_(triangle)
{
  std::array<Vertex, 3> vertices=
  {
    Vertex{Position{-1, -1, 0}, Material{Color{255, 0, 0, 1}}},
    Vertex{Position{0, 1, 0}, Material{Color{0, 255, 0, 1}}},
    Vertex{Position{1, -1, 0}, Material{Color{0, 0, 255, 1}}}
  };

  std::array<float, 6 * 3> vertexData;
  const auto depth1 = 0.2;
  const auto depth2 = 0.3;
  vertexData[0] = -1;
  vertexData[1] = -1;
  vertexData[2] = 0.1;

  vertexData[3] = 0;
  vertexData[4] = 1;
  vertexData[5] = 0.2;

  vertexData[6] = 1;
  vertexData[7] = -1;
  vertexData[8] = 0.3;


  vertexData[9] = -1;
  vertexData[10] = 1;
  vertexData[11] = 0.2;

  vertexData[12] = 0;
  vertexData[13] = -1;
  vertexData[14] = 0.2;

  vertexData[15] = 1;
  vertexData[16] = 1;
  vertexData[17] = 0.2;

  std::array<float, 9 * 2> colorData = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0

  };


  // Enable alpha
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);

  glGenBuffers(1, &vboPosition_);
  glBindBuffer(GL_ARRAY_BUFFER, vboPosition_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &vboColor_);
  glBindBuffer(GL_ARRAY_BUFFER, vboColor_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &vboVertices_);
  glBindBuffer(GL_ARRAY_BUFFER, vboVertices_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

  const char* vertexPositionName = "vertexPosition";
  vertexPositionAttr_ = glGetAttribLocation(programId, vertexPositionName);

  const char* vertexColorName = "vertexColor";
  vertexColorAttr_ = glGetAttribLocation(programId, vertexColorName);


  const char* fadeName = "fade";
  fadeUniform_ = glGetUniformLocation(programId, fadeName);
  glUniform1f(fadeUniform_, 0.1);


  glEnableVertexAttribArray(vertexPositionAttr_);
  glEnableVertexAttribArray(vertexColorAttr_);
  glBindBuffer(GL_ARRAY_BUFFER, vboPosition_);
  const int cVertexPositionDim = 3;
  glVertexAttribPointer(
    vertexPositionAttr_, // attribute
    cVertexPositionDim,              // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0);                // offset of first element


  glBindBuffer(GL_ARRAY_BUFFER, vboColor_);
  const int cVertexColorDim = 3;
  glVertexAttribPointer(
    vertexColorAttr_, // attribute
    cVertexColorDim,              // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0);                // offset of first element

 }

 TriangleSprite::~TriangleSprite()
{
   glDisableVertexAttribArray(vertexColorAttr_);
   glDisableVertexAttribArray(vertexPositionAttr_);

   if (vboPosition_)
  {
    glDeleteBuffers(1, &vboPosition_);
  }
}


void TriangleSprite::render(int x, int y)
{
  glUniform1f(fadeUniform_, y / 480.0);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}


