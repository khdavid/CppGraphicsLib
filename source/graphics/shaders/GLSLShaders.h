#pragma once

#include <glew.h>

class GLSLShaders
{
public:
  GLSLShaders();
private:
  GLuint programId_ = 0;
  GLuint vertexShaderId_ = 0;
  GLuint fragmentShaderId_ = 0;
  
  void compileShader_(GLuint& id, GLuint type, const std::string& shaderCode);
  void linkShaders_();
};

