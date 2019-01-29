#pragma once

#include <glew.h>

#include "listeners/inputEventListener.h"

class GLSLShaderToolBase : public InputEventListener
{
public:
  GLSLShaderToolBase::GLSLShaderToolBase(
    const std::string& vertexShaderCode,
    const std::string& fragmentShaderCode);
    ~GLSLShaderToolBase();

  GLuint getProgramId() const;
private:
  GLuint programId_ = 0;
  GLuint vertexShaderId_ = 0;
  GLuint fragmentShaderId_ = 0;
  
  void compileShader_(GLuint& id, GLuint type, const std::string& shaderCode);
  void linkShaders_();
};

