#include <vector>

#include "nodes/graphicsNode.h"
#include "mondelbrotSprite.h"


namespace
{
  const char* cFadeName = "fade";

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

void MondelbrotSprite::init()
{
  TriangleSprite::init(cVertices);
  fadeUniform_ = glGetUniformLocation(programId_, cFadeName);
}

void MondelbrotSprite::render(int x, int y)
{
  glUniform1f(fadeUniform_, y / 480.0f);
  TriangleSprite::render(x, y);
}

std::string MondelbrotSprite::getVertexShaderCode_() const
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

std::string MondelbrotSprite::getFragmentShaderCode_() const
{
  return R"(

  #version 130
  
  out vec4 color;
  uniform float fade;
  
  struct ComplexNumber
  {
    float Real;
    float Imagine;
  };
  
  ComplexNumber Product(ComplexNumber first, ComplexNumber second)
  {
    ComplexNumber result;  
    result.Real = first.Real * second.Real - first.Imagine * second.Imagine;
    result.Imagine = first.Real * second.Imagine + first.Imagine * second.Real;
    return result;
  }
  
  ComplexNumber Add(ComplexNumber first, ComplexNumber second)
  {
    ComplexNumber result;  
    result.Real = first.Real + second.Real;
    result.Imagine = first.Imagine + second.Imagine;
    return result;
  }
  
  float length(ComplexNumber number)
  {
     return sqrt(number.Real * number.Real + number.Imagine * number.Imagine);
  }
  
  float length2(ComplexNumber number)
  {
     return number.Real * number.Real + number.Imagine * number.Imagine;
  }
  
  void main()
  {
    ComplexNumber z;
       z.Real = 0;
       z.Imagine = 0;
  
    for (int i = 0; i < 100; i++)
    {
       ComplexNumber c;
       c.Real = (gl_FragCoord.x - 320 ) / 640 * fade;
       c.Imagine = (gl_FragCoord.y -900) / 320 * fade; 
       z = Add (Product(Product(z,z),z), Product(c,c));
       if (length2(z) < 0.001) break;
       if (length2(z) > 100) break;
    }
    float len = length(z);
    color = vec4(100 + len*len, sqrt(len), len, 1);
  }
  
  )";
}
