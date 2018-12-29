#pragma once

#include <glew.h>

#include "listeners/mouseEventListener.h"

class GLSLShaderToolBase : public MouseEventListener
{
public:
  GLSLShaderToolBase();
  ~GLSLShaderToolBase();

  void use();
  void unuse();
private:
  GLuint programId_ = 0;
  GLuint vertexShaderId_ = 0;
  GLuint fragmentShaderId_ = 0;
  GLuint numAttributes_ = 0;
  
  void compileShader_(GLuint& id, GLuint type, const std::string& shaderCode);
  void linkShaders_();
  void addAttribute_(const std::string& name);
};

