#include <array>

#include "nodes/graphicsNode.h"
#include "tools/GLSLShaderToolBase.h"
#include "triangleSprite.h"



TriangleSprite::TriangleSprite()
{
  shaderProgram_ = std::make_unique<GLSLShaderToolBase>(getVertexShaderCode_(), getFragmentShaderCode_());
  auto programId = shaderProgram_->getProgramId();
  std::array<Vertex, 12> vertices=
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

  // Enable alpha
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);

  glGenBuffers(1, &vboVertices_);
  glBindBuffer(GL_ARRAY_BUFFER, vboVertices_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

  const char* vertexPositionName = "vertexPosition";
  vertexPositionAttr_ = glGetAttribLocation(programId, vertexPositionName);

  const char* vertexColorName = "vertexColor";
  vertexColorAttr_ = glGetAttribLocation(programId, vertexColorName);


  const char* fadeName = "fade";
  fadeUniform_ = glGetUniformLocation(programId, fadeName);
  glUniform1f(fadeUniform_, 1);


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

void TriangleSprite::init()
{

}


 TriangleSprite::~TriangleSprite()
{
   glDisableVertexAttribArray(vertexColorAttr_);
   glDisableVertexAttribArray(vertexPositionAttr_);

   if (vboVertices_)
  {
    glDeleteBuffers(1, &vboVertices_);
  }
}


void TriangleSprite::render(int x, int y)
{
  glUniform1f(fadeUniform_, y / 480.0);
  glDrawArrays(GL_TRIANGLES, 0, 12);
}

std::string TriangleSprite::getVertexShaderCode_() const
{
  return R"(

  #version 130
  
  in vec3 vertexPosition;
  in vec3 vertexColor;
  varying vec3 varyingColor;
  uniform float fade;
  
  
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

std::string TriangleSprite::getFragmentShaderCode_() const
{
  return R"(

  #version 130
  
  out vec4 color;
  varying vec3 varyingColor;
  uniform float fade;
  
  
  void main()
  {
    color.xyz = varyingColor.rgb * fade * 20;
    color.w = 0.6f;
  }
  
  )";
}


