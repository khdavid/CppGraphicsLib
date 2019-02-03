#include "fragmentShaderSprite.h"

namespace
{
std::vector<Vertex> cVertices =
{
  Vertex{Position{-1, 1, 0}, Material{Color{0, 0, 0}}},
  Vertex{Position{1, -1, 0}, Material{Color{0, 0, 0}}},
  Vertex{Position{-1, -1, 0}, Material{Color{0, 0, 0}}},
  Vertex{Position{-1, 1, 0}, Material{Color{0, 0, 0}}},
  Vertex{Position{1, -1, 0}, Material{Color{0, 0, 0}}},
  Vertex{Position{1, 1, 0}, Material{Color{0, 0, 0}}},
};
}

void FragmentShaderSprite::init()
{
  init_(cVertices);
}

std::string FragmentShaderSprite::getVertexShaderCode_() const
{
  return R"(

  #version 130
  
  in vec3 vertexPosition;  
  
  void main()
  {
    gl_Position.x = vertexPosition[0];
    gl_Position.y = vertexPosition[1];
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
  
  }
  )";
}

