#include <vector>
#include <iostream>
#include "GLSLShaderCompiler.h"

GLSLShaderCompiler::GLSLShaderCompiler(
  const std::string& vertexShaderCode,
  const std::string& fragmentShaderCode)
{
  programId_ = glCreateProgram();
  compileShader_(vertexShaderId_, GL_VERTEX_SHADER, vertexShaderCode);
  compileShader_(fragmentShaderId_, GL_FRAGMENT_SHADER, fragmentShaderCode);
  linkShaders_();
  glUseProgram(programId_);
}

GLSLShaderCompiler::~GLSLShaderCompiler()
{
  glDeleteProgram(programId_);
}

void GLSLShaderCompiler::compileShader_(GLuint& id, GLuint type, const std::string& shaderCode)
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

void GLSLShaderCompiler::linkShaders_()
{

  glAttachShader(programId_, vertexShaderId_);
  glAttachShader(programId_, fragmentShaderId_);

  glLinkProgram(programId_);

  GLint isLinked = 0;
  glGetProgramiv(programId_, GL_LINK_STATUS, &isLinked);

  if (isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(programId_, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<char> errorLog(maxLength);
    glGetShaderInfoLog(programId_, maxLength, &maxLength, errorLog.data());
    std::cout << "SHADER COMPILING " << errorLog.data() << std::endl;
    glDeleteProgram(programId_);
  }
  else
  {
    glDetachShader(programId_, vertexShaderId_);
    glDetachShader(programId_, fragmentShaderId_);
  }
  glDeleteShader(vertexShaderId_);
  glDeleteShader(fragmentShaderId_);
}

GLuint GLSLShaderCompiler::getProgramId() const
{
  return programId_;
}


