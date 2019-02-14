#pragma once
#include "GLSL/GLSLProgramTriangle.h"
class GLSLProgramFragmentShader : public GLSLProgramTriangle
{
public:
  using GLSLProgramTriangle::GLSLProgramTriangle;
  virtual void init() override;
private:
  std::string getVertexShaderCode_() const override;

};

