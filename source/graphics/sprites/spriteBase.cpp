#include "SpriteBase.h"

void SpriteBase::init()
{
  shaderProgram_ = std::make_unique<GLSLShaderToolBase>(getVertexShaderCode_(), getFragmentShaderCode_());
  programId_ = shaderProgram_->getProgramId();

  // Enable alpha
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
}

void SpriteBase::enable()
{
  glUseProgram(programId_);
}
