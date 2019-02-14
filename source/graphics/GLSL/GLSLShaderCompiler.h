#pragma once

#include <glew.h>

#include "listeners/inputEventListener.h"

class GLSLShaderCompiler
{
public:
  GLSLShaderCompiler::GLSLShaderCompiler(
    const std::string& vertexShaderCode,
    const std::string& fragmentShaderCode);
    ~GLSLShaderCompiler();

  GLuint getProgramId() const;
private:
  GLuint programId_ = 0;
  GLuint vertexShaderId_ = 0;
  GLuint fragmentShaderId_ = 0;
  
  void compileShader_(GLuint& id, GLuint type, const std::string& shaderCode);
  void linkShaders_();
};

