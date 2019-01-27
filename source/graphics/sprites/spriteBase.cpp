#include "SpriteBase.h"

void SpriteBase::init()
{
  shaderProgram_ = std::make_unique<GLSLShaderToolBase>(getVertexShaderCode_(), getFragmentShaderCode_());
  programId_ = shaderProgram_->getProgramId();
}
