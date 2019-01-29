#pragma once

#include <string>
#include <glew.h>
#include "tools/GLSLShaderToolBase.h"

class SpriteBase
{
public:
  virtual ~SpriteBase() = default;
  virtual void render(int x, int y) = 0;
protected:
  void init_();
  std::unique_ptr<GLSLShaderToolBase> shaderProgram_;
  GLuint programId_ = 0;
private:
  virtual std::string getVertexShaderCode_() const = 0;
  virtual std::string getFragmentShaderCode_() const = 0;

};
