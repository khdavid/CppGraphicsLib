#pragma once
#include "fragmentShaderSprite.h"

class RayTracingSprite : public FragmentShaderSprite
{
public:
  using FragmentShaderSprite::FragmentShaderSprite;
  //virtual void init() override;

private:
  virtual std::string getFragmentShaderCode_() const;

};

