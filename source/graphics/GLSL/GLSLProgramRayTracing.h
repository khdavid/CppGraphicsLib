#pragma once
#include "geometryObjects/matrix.h"
#include "geometryObjects/point.h"

#include "GLSLProgramFragmentShader.h"

class GLSLProgramRayTracing : public GLSLProgramFragmentShader
{
public:
  GLSLProgramRayTracing(SDL_Window& window);
  virtual void init() override;
  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseMovePassive(int x, int y) override;
  virtual void onMouseScrolling(int velocity) override;
  virtual void render() override;

private:
  virtual std::string getFragmentShaderCode_() const;
  Matrix4D globalToCamera_;
  double angle_ = 0;
  GLint globalToCameraUniform_ = 0;
  Point2D mousePoint_;


};

