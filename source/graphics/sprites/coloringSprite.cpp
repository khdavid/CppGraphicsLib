#include <array>

#include "nodes/graphicsNode.h"
#include "tools/GLSLShaderToolBase.h"
#include "coloringSprite.h"

namespace
{
  const char* cFadeName = "fade";
}

void ColoringSprite::init(const std::vector<Vertex>& vertices)
{
  TriangleSprite::init(vertices);
  fadeUniform_ = glGetUniformLocation(programId_, cFadeName);
}

void ColoringSprite::onMouseMovePassive(int, int y)
{
  glUniform1f(fadeUniform_, y / 480.0f);
  render();
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


