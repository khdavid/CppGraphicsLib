#pragma once

#include <vector>
#include <glew.h>

#include "nodes/graphicsNode.h"
#include "geometryObjects/triangle.h"
#include "spriteBase.h"
#include "triangleSprite.h"

class GLSLShaderToolBase;

class ColoringSprite : public TriangleSprite
{
public:
  using TriangleSprite::TriangleSprite;
  virtual void onMouseMovePassive(int x, int y) override;
  virtual void init() override;

private:
  virtual std::string getVertexShaderCode_() const;
  virtual std::string getFragmentShaderCode_() const;

  GLint fadeUniform_ = 0;
};

