#pragma once
#include "fragmentShaderSprite.h"

class MandelbrotSprite : public FragmentShaderSprite
{
public:
  using FragmentShaderSprite::FragmentShaderSprite;
  virtual void init() override;
  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseScrolling(int velocity) override;

private:
  GLint fadeUniform_ = 0;
  GLint xShiftUniform_ = 0;
  GLint yShiftUniform_ = 0;
  int xPrev_ = 0;
  int yPrev_ = 0;
  double xShift_ = 640.0 / 2;
  double yShift_ = 480.0 / 2;
  
  double fade_ = 0.01;

  virtual std::string getFragmentShaderCode_() const;
};
