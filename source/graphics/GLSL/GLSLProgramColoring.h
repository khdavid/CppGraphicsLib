#pragma once

#include <vector>
#include <glew.h>

#include "nodes/graphicsNode.h"
#include "geometryObjects/triangle.h"
#include "GLSL/GLSLProgramBase.h"
#include "GLSL/GLSLProgramTriangle.h"

class GLSLShaderCompiler;

class GLSLProgramColoring : public GLSLProgramTriangle
{
public:
  using GLSLProgramTriangle::GLSLProgramTriangle;
  virtual void onMouseMovePassive(int x, int y) override;
  virtual void init() override;

private:
  virtual std::string getVertexShaderCode_() const;
  virtual std::string getFragmentShaderCode_() const;

  GLint fadeUniform_ = 0;
};

