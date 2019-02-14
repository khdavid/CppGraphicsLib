#pragma once

#include <string>
#include <SDL.h>
#include <glew.h>

#include "listeners/inputEventListener.h"
#include "GLSL/GLSLShaderCompiler.h"

class SpriteBase : public InputEventListener
{
public:
  virtual ~SpriteBase() = default;
  virtual void render() = 0;
  virtual void init() = 0;

protected:
  void init_();

  std::unique_ptr<GLSLShaderCompiler> shaderProgram_;
  GLuint programId_ = 0;

private:
  virtual std::string getVertexShaderCode_() const = 0;
  virtual std::string getFragmentShaderCode_() const = 0;

};
