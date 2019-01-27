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
  void render(int x, int y);

private:
  std::string getVertexShaderCode_() const;
  std::string getFragmentShaderCode_() const;
  GLuint vboVertices_;
  GLint vertexPositionAttr_ = 0;
  GLint vertexColorAttr_ = 0;
  GLint fadeUniform_ = 0;
  std::unique_ptr<GLSLShaderToolBase> shaderProgram_;
};

