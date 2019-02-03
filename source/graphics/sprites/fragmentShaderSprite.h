#pragma once
#include "triangleSprite.h"
class FragmentShaderSprite : public TriangleSprite
{
public:
  using TriangleSprite::TriangleSprite;
  virtual void init() override;
private:
  std::string getVertexShaderCode_() const override;

};

