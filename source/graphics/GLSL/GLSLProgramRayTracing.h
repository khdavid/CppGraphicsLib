#pragma once
#include "geometryObjects/matrix.h"
#include "geometryObjects/point.h"

#include "GLSLProgramFragmentShader.h"

class Model;

class GLSLProgramRayTracing : public GLSLProgramFragmentShader
{
public:
  GLSLProgramRayTracing(SDL_Window& window, const Model& model);
  virtual void init() override;
  virtual void render() override;
  Matrix4D getGlobalToCamera() const;
  void setGlobalToCamera(Matrix4D matrix);

private:
  virtual std::string getFragmentShaderCode_() const;
  const Model& model_;
  Matrix4D globalToCamera_;
  GLint globalToCameraUniform_ = 0;
  GLint RGBColorsUniform_ = 0;


};

