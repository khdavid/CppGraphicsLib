#pragma once

#include <string>
#include <glew.h>
#include "tools/GLSLShaderToolBase.h"

class SpriteBase
{
public:
  virtual ~SpriteBase() = default;
  virtual void render(int x, int y) = 0;
  virtual void onMouseClick(int x, int y);
  virtual void onMouseRelease(int x, int y);
  virtual void onMouseMove(int x, int y);
  virtual void onMouseScrolling(int velocity);


protected:
  void init_();
  std::unique_ptr<GLSLShaderToolBase> shaderProgram_;
  GLuint programId_ = 0;
private:
  virtual std::string getVertexShaderCode_() const = 0;
  virtual std::string getFragmentShaderCode_() const = 0;

};
