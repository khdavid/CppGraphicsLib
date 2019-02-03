#include <vector>

#include "nodes/graphicsNode.h"
#include "RayTracingSprite.h"


std::string RayTracingSprite::getFragmentShaderCode_() const
{
  return R"(

  #version 130
  
  out vec4 color;
  
  void main()
  {

    const vec4 blue = vec4(166, 202, 240, 255) / 255;
    color = blue;  
  }
  
  )";

}
