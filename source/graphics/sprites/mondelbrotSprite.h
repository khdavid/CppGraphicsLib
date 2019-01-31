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
  virtual void onWindowsResized(int, int) override;

private:
  GLint fadeUniform_ = 0;
  GLint xShiftUniform_ = 0;
  GLint yShiftUniform_ = 0;
  int xPrev_ = 0;
  int yPrev_ = 0;
  float xShift_ = 640.f / 2;
  float yShift_ = 480.f / 2;
  
  int width_ = 640;
  int height_ = 480;
  float fade_ = 0.01f;

  virtual std::string getVertexShaderCode_() const;
  virtual std::string getFragmentShaderCode_() const;
};

