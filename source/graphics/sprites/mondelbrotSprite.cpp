#include <vector>
#include <iostream>

#include "nodes/graphicsNode.h"
#include "utils/SDLUtils.h"
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
  glUniform1f(xShiftUniform_, xShift_);
  glUniform1f(yShiftUniform_, yShift_);

}

void MondelbrotSprite::onMouseClick(int x, int y)
{
  xPrev_ = x;
  yPrev_ = y;
  render();
}

void MondelbrotSprite::onMouseMove(int x, int y)
{
  xShift_ += (x - xPrev_);
  yShift_ += -(y - yPrev_);
  xPrev_ = x;
  yPrev_ = y;
  
  glUniform1f(xShiftUniform_, xShift_);
  glUniform1f(yShiftUniform_, yShift_);
  render();

}

void MondelbrotSprite::onMouseScrolling(int velocity)
{
  auto mouseCoord = SDLUtils::getMouseXY();
  auto x = mouseCoord.first;
  auto y = mouseCoord.second;
  std::cout << "scrolling " << "x " << mouseCoord.first << "y " << mouseCoord.second << std::endl;
  
  auto sizes = SDLUtils::getScreenSizes();
  y = sizes.second - y;

  auto fadeOld = fade_;

  fade_ *= (1 + velocity / 50.f);

  //(x-xs)f = (x-XS)F
  //XS = x - (x-xs)f/F
  xShift_ = x - (x - xShift_) * fadeOld / fade_;
  yShift_ = y - (y - yShift_) * fadeOld / fade_;

  glUniform1f(fadeUniform_, fade_);
  glUniform1f(xShiftUniform_, xShift_);
  glUniform1f(yShiftUniform_, yShift_);

  render();
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
  uniform float xShift;
  uniform float yShift;


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
  
    const int nMax = 1000;
    int i = 0;
    for (i = 0; i < nMax; i++)
    {
       ComplexNumber c;
       c.Real = (gl_FragCoord.x - xShift ) * fade;
       c.Imagine = (gl_FragCoord.y - yShift) * fade; 
       z = Add (Product(z,z), c);
       if (length2(z) > 4) break;
    }
    float k = float (i) / nMax;
    if (i < nMax / 3)
    {
       color = vec4(1. - 2. * k * k , 1. - 2. * k, 2. * k, 1);
    }
    else if (i < 2 * nMax / 3)
    {
       color = vec4(1.0 - 0.2 * k, 0.5 * k, 1. - 0.3 * k, 1);
    }
    else
    {
       color = vec4(1. - 2. * k , 1. - 2. * k, 2. * k, 1);
    }
  }
  
  )";
}
