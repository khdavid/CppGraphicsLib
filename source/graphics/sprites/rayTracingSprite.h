#pragma once
#include "geometryObjects/matrix.h"

#include "fragmentShaderSprite.h"

class RayTracingSprite : public FragmentShaderSprite
{
public:
  RayTracingSprite(SDL_Window& window);
  virtual void init() override;
  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseMovePassive(int x, int y) override;
  virtual void onMouseScrolling(int velocity) override;

private:
  virtual std::string getFragmentShaderCode_() const;
  Matrix4D globalToCamera_;

  GLint globalToCameraUniform_ = 0;

};

