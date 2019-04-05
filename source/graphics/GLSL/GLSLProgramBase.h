#pragma once

#include <string>
#include <memory>
#include <glew.h>

#include "listeners/inputEventListener.h"
#include "GLSL/GLSLShaderCompiler.h"

class GLSLProgramBase : public InputEventListener
{
public:
  virtual ~GLSLProgramBase();
  virtual void render() = 0;
  virtual void init() = 0;
  virtual void onWindowsResized(int x, int y) override;


protected:
  void init_();

  std::unique_ptr<GLSLShaderCompiler> shaderProgram_;
  GLuint programId_ = 0;

private:
  virtual std::string getVertexShaderCode_() const = 0;
  virtual std::string getFragmentShaderCode_() const = 0;

};
