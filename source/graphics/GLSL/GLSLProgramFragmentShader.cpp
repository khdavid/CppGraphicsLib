#include "GLSLProgramFragmentShader.h"

namespace
{
std::vector<GLVertex> cVertices =
{
  GLVertex{GLPosition{-1, 1, 0}, GLMaterial{GLColor{0, 0, 0}}},
  GLVertex{GLPosition{1, -1, 0}, GLMaterial{GLColor{0, 0, 0}}},
  GLVertex{GLPosition{-1, -1, 0}, GLMaterial{GLColor{0, 0, 0}}},
  GLVertex{GLPosition{-1, 1, 0}, GLMaterial{GLColor{0, 0, 0}}},
  GLVertex{GLPosition{1, -1, 0}, GLMaterial{GLColor{0, 0, 0}}},
  GLVertex{GLPosition{1, 1, 0}, GLMaterial{GLColor{0, 0, 0}}},
};
}

void GLSLProgramFragmentShader::init()
{
  init_(cVertices);
}

std::string GLSLProgramFragmentShader::getVertexShaderCode_() const
{
  return R"(

  #version 130
  
  in vec3 vertexPosition;  
  
  void main()
  {
    gl_Position.x = vertexPosition[0];
    gl_Position.y = vertexPosition[1];
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
  
  }
  )";
}

