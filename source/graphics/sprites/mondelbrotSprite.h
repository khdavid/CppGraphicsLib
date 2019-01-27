#pragma once
#include "spriteBase.h"

class MondelbrotSprite : public SpriteBase
{
public:
  virtual void init() override;
  virtual void render(int x, int y);
private:
  GLuint vboVertices_ = 0;
  GLint vertexPositionAttr_ = 0;
  GLint fadeUniform_ = 0;

  virtual std::string getVertexShaderCode_() const;
  virtual std::string getFragmentShaderCode_() const;
};

