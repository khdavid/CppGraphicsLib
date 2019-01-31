#pragma once
#include "triangleSprite.h"

class MondelbrotSprite : public TriangleSprite
{
public:
  using TriangleSprite::TriangleSprite;
  void init();
  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseScrolling(int velocity) override;

private:
  GLint fadeUniform_ = 0;
  GLint xShiftUniform_ = 0;
  GLint yShiftUniform_ = 0;
  int xPrev_ = 0;
  int yPrev_ = 0;
  int xShift_ = 0;
  int yShift_ = 0;
  float fade_ = 0.01f;

  virtual std::string getVertexShaderCode_() const;
  virtual std::string getFragmentShaderCode_() const;
};

