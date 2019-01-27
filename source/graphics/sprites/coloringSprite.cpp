#include <array>

#include "nodes/graphicsNode.h"
#include "tools/GLSLShaderToolBase.h"
#include "coloringSprite.h"

namespace
{
  const char* cVertexPositionName = "vertexPosition";
  const char* cVertexColorName = "vertexColor";
  const char* cFadeName = "fade";

  std::array<Vertex, 12> cVertices =
  {
    Vertex{Position{-1, -1, 0.1}, Material{Color{255, 0, 0}}},
    Vertex{Position{0, 1, 0.2}, Material{Color{0, 255, 0}}},
    Vertex{Position{1, -1, 0.3}, Material{Color{0, 0, 255}}},
    Vertex{Position{-1, 1, 0.3}, Material{Color{0, 0, 255}}},
    Vertex{Position{0, -1, 0.2}, Material{Color{255, 0, 0}}},
    Vertex{Position{1, 1, 0.1}, Material{Color{0, 255, 0}}},
    Vertex{Position{-1, 1, 0.3}, Material{Color{0, 0, 255}}},
    Vertex{Position{1, 0, 0.2}, Material{Color{255, 0, 0}}},
    Vertex{Position{-1, -1, 0.1}, Material{Color{0, 255, 0}}},
    Vertex{Position{1, 1, 0.1}, Material{Color{0, 0, 255}}},
    Vertex{Position{-1, 0, 0.2}, Material{Color{255, 0, 0}}},
    Vertex{Position{1, -1, 0.3}, Material{Color{255, 255, 255}}}
  };

}
void ColoringSprite::init()
{
  SpriteBase::init();
  
  glGenBuffers(1, &vboVertices_);
  glBindBuffer(GL_ARRAY_BUFFER, vboVertices_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cVertices), cVertices.data(), GL_STATIC_DRAW);

  vertexPositionAttr_ = glGetAttribLocation(programId_, cVertexPositionName);
  vertexColorAttr_ = glGetAttribLocation(programId_, cVertexColorName);
  fadeUniform_ = glGetUniformLocation(programId_, cFadeName);

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


 ColoringSprite::~ColoringSprite()
{
   if (shaderProgram_)
  {
    glDeleteBuffers(1, &vboVertices_);
    glDisableVertexAttribArray(vertexColorAttr_);
    glDisableVertexAttribArray(vertexPositionAttr_);
  }
}


void ColoringSprite::render(int x, int y)
{
  glUniform1f(fadeUniform_, y / 480.0);
  glDrawArrays(GL_TRIANGLES, 0, 12);
}

std::string ColoringSprite::getVertexShaderCode_() const
{
  return R"(

  #version 130
  
  in vec3 vertexPosition;
  in vec3 vertexColor;
  out vec3 varyingColor;
  
  
  void main()
  {
    gl_Position.x = vertexPosition[0];
    gl_Position.y = vertexPosition[1];
    gl_Position.z = vertexPosition[2];
    gl_Position.w = 1.0;
  
    varyingColor = vertexColor / 256.0;
  }

  )";
}

std::string ColoringSprite::getFragmentShaderCode_() const
{
  return R"(

  #version 130
  
  out vec4 color;
  in vec3 varyingColor;
  uniform float fade;
  
  
  void main()
  {
    color.xyz = varyingColor.rgb * fade * 20;
    color.w = 0.6f;
  }
  
  )";
}


