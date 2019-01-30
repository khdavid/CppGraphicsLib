#include <vector>

#include "nodes/graphicsNode.h"
#include "mondelbrotSprite.h"


namespace
{
  const char* cFadeName = "fade";
  const char* cXShift = "xShift";
  const char* cYShift = "yShift";

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
  xShiftUniform_ = glGetUniformLocation(programId_, cXShift);
  yShiftUniform_ = glGetUniformLocation(programId_, cYShift);

  glUniform1f(fadeUniform_, fade_);
}

void MondelbrotSprite::render(int x, int y)
{
  TriangleSprite::render(x, y);
}

void MondelbrotSprite::onMouseClick(int x, int y)
{
  xPrev_ = x;
  yPrev_ = y;
}

void MondelbrotSprite::onMouseMove(int x, int y)
{
  xShift_ += (x - xPrev_);
  yShift_ += (y - yPrev_);
  xPrev_ = x;
  yPrev_ = y;
  
  glUniform1i(xShiftUniform_, xShift_);
  glUniform1i(yShiftUniform_, yShift_);
  TriangleSprite::render(x, y);

}

void MondelbrotSprite::onMouseScrolling(int velocity)
{
  fade_ += velocity / 50.f;
  glUniform1f(fadeUniform_, fade_);
  TriangleSprite::render(0, 0);
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
  uniform int xShift;
  uniform int yShift;


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
       c.Real = (gl_FragCoord.x - xShift ) / 640 * fade;
       c.Imagine = (gl_FragCoord.y + yShift) / 320 * fade; 
       z = Add (Product(z,z), c);
       if (length2(z) < 0.001) break;
       if (length2(z) > 100) break;
    }
    float len = length(z);
    color = vec4(100 + len*len, sqrt(len), len, 1);
  }
  
  )";
}
