#pragma once
#include "geometryObjects/matrix.h"
#include "geometryObjects/point.h"

#include "GLSLProgramFragmentShader.h"

class GLSLProgramRayTracing : public GLSLProgramFragmentShader
{
public:
  GLSLProgramRayTracing(SDL_Window& window);
  virtual void init() override;
  virtual void render() override;
  Matrix4D getGlobalToCamera() const;
  void setGlobalToCamera(Matrix4D matrix);

private:
  virtual std::string getFragmentShaderCode_() const;
  Matrix4D globalToCamera_;
  double angle_ = 0;
  GLint globalToCameraUniform_ = 0;
  Point2D mousePoint_;


};

