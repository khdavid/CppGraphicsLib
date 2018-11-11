#include <vector>
#include <iostream>
#include "GLSLShaders.h"
#include "vertexShader.h"
#include "fragmentShader.h"

GLSLShaders::GLSLShaders()
{
  compileShader_(vertexShaderId_, GL_VERTEX_SHADER, cVertexShaderCode);
  compileShader_(fragmentShaderId_, GL_FRAGMENT_SHADER, cFragmentShaderCode);
}

void GLSLShaders::compileShader_(GLuint& id, GLuint type, const std::string& shaderCode)
{
  id = glCreateShader(type);
  if (!id)
  {
    std::cout << "Cannot create shader" << std::endl;
  }
  const char* code = shaderCode.c_str();
  glShaderSource(id, 1, &code, nullptr);
  glCompileShader(id);

  GLint success = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<char> errorLog(maxLength);
    glGetShaderInfoLog(id, maxLength, &maxLength, errorLog.data());
    std::cout << "SHADER COMPILING " << errorLog.data() << std::endl;
    glDeleteShader(id);
    return;

  }

  
}

void GLSLShaders::linkShaders_()
{
}

