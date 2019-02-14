#include <array>

#include "nodes/graphicsNode.h"
#include "GLSL/GLSLShaderCompiler.h"
#include "GLSLProgramColoring.h"

namespace
{
const char* cFadeName = "fade";
std::vector<GLVertex> cColoringSpriteVertices =
{
  GLVertex{GLPosition{-1.f, -1.f, 0.1f}, GLMaterial{GLColor{255, 0, 0}}},
  GLVertex{GLPosition{0.f, 1.f, 0.2f}, GLMaterial{GLColor{0, 255, 0}}},
  GLVertex{GLPosition{1.f, -1.f, 0.3f}, GLMaterial{GLColor{0, 0, 255}}},
  GLVertex{GLPosition{-1.f, 1.f, 0.3f}, GLMaterial{GLColor{0, 0, 255}}},
  GLVertex{GLPosition{0.f, -1.f, 0.2f}, GLMaterial{GLColor{255, 0, 0}}},
  GLVertex{GLPosition{1.f, 1.f, 0.1f}, GLMaterial{GLColor{0, 255, 0}}},
  GLVertex{GLPosition{-1.f, 1.f, 0.3f}, GLMaterial{GLColor{0, 0, 255}}},
  GLVertex{GLPosition{1.f, 0.f, 0.2f}, GLMaterial{GLColor{255, 0, 0}}},
  GLVertex{GLPosition{-1.f, -1.f, 0.1f}, GLMaterial{GLColor{0, 255, 0}}},
  GLVertex{GLPosition{1.f, 1.f, 0.1f}, GLMaterial{GLColor{0, 0, 255}}},
  GLVertex{GLPosition{-1.f, 0.f, 0.2f}, GLMaterial{GLColor{255, 0, 0}}},
  GLVertex{GLPosition{1.f, -1.f, 0.3f}, GLMaterial{GLColor{255, 255, 255}}}
};
}

void GLSLProgramColoring::init()
{
  init_(cColoringSpriteVertices);
  fadeUniform_ = glGetUniformLocation(programId_, cFadeName);
}

void GLSLProgramColoring::onMouseMovePassive(int, int y)
{
  glUniform1f(fadeUniform_, y / 480.0f);
  render();
}


std::string GLSLProgramColoring::getVertexShaderCode_() const
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

std::string GLSLProgramColoring::getFragmentShaderCode_() const
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


