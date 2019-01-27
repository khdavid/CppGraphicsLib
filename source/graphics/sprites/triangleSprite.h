#pragma once

#include <glew.h>

#include "geometryObjects/triangle.h"
#include "spriteBase.h"

class GLSLShaderToolBase;

class TriangleSprite : public SpriteBase
{
public:
  ~TriangleSprite();
  virtual void init() override;
  virtual void render(int x, int y) override;

private:
  virtual std::string getVertexShaderCode_() const;
  virtual std::string getFragmentShaderCode_() const;

  GLuint vboVertices_ = 0;
  GLint vertexPositionAttr_ = 0;
  GLint vertexColorAttr_ = 0;
  GLint fadeUniform_ = 0;
};

