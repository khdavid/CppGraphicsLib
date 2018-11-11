#include <vector>
#include <iostream>
#include "GLSLShaders.h"
#include "vertexShader.h"
#include "fragmentShader.h"

GLSLShaders::GLSLShaders()
{
  compileShader_(vertexShaderId_, GL_VERTEX_SHADER, cVertexShaderCode);
  compileShader_(fragmentShaderId_, GL_FRAGMENT_SHADER, cFragmentShaderCode);
  addAttribute_("vertexPosition");
  linkShaders_();
}

void GLSLShaders::use()
{
  glUseProgram(programId_);
  for (int i = 0; i < numAttributes_; ++i)
  {
    glEnableVertexAttribArray(i);
  }
}
void GLSLShaders::unuse()
{
  glUseProgram(0);
  for (int i = 0; i < numAttributes_; ++i)
  {
    glDisableVertexAttribArray(i);
  }

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
  programId_ = glCreateProgram();

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

void GLSLShaders::addAttribute_(const std::string & name)
{
  glBindAttribLocation(programId_, numAttributes_++, name.c_str());
}

