#pragma once

#include <string>
#include <SDL.h>
#include <glew.h>

#include "listeners/inputEventListener.h"
#include "tools/GLSLShaderToolBase.h"

class SpriteBase : public InputEventListener
{
public:
  SpriteBase(SDL_Window& window);
  virtual ~SpriteBase() = default;
  virtual void render() = 0;

protected:
  void init_();

  std::unique_ptr<GLSLShaderToolBase> shaderProgram_;
  GLuint programId_ = 0;
  SDL_Window& window_;

private:
  virtual std::string getVertexShaderCode_() const = 0;
  virtual std::string getFragmentShaderCode_() const = 0;

};
