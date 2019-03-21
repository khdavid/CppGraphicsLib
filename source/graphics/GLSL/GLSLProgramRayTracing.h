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
  virtual void onWindowsResized(int x, int y) override;
  Matrix4D getGlobalToCamera() const;
  void setGlobalToCamera(Matrix4D matrix);

private:
  virtual std::string getFragmentShaderCode_() const;
  void initSpheresUniforms_();
  void renderSpheres_();

  const Model& model_;
  Matrix4D globalToCamera_;

  struct GlobalUniform
  {
    GLint globalToCamera = 0;
    GLint screenSize = 0;
  };

  struct MaterialsUniform
  {
    GLint diffuse = 0;
    GLint specular = 0;
    GLint ambient = 0;
  };
  struct SpheresGeometryUniform
  {
    GLint radius = 0;
    GLint center = 0;
    GLint count = 0;
  };

  MaterialsUniform sphereMaterialUniform_;
  SpheresGeometryUniform spheresGeometryUniform_;
  GlobalUniform globalUniform_;

};

