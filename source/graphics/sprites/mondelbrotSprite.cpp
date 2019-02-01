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
  init_(cVertices);
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

  auto alpha = std::max(-0.5f, velocity / 50.f);
  fade_ *= (1 + alpha);

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
  
  vec4 linearExtrapolation(const vec4 first, const vec4 last, float min, float max, float x)
  {
    return first + (x - min) * (last - first) / (max - min);
  }
  
  void main()
  {
    ComplexNumber z;
       z.Real = 0;
       z.Imagine = 0;
  
    const int nMax = 500;
    int i = 0;

    ComplexNumber c;
    c.Real = (gl_FragCoord.x - xShift ) * fade;
    c.Imagine = (gl_FragCoord.y - yShift) * fade; 

    for (i = 0; i < nMax; i++)
    {
       z = Add (Product(z,z), c);
       if (length2(z) > 4) break;
    }
    
    float k = float (i) / nMax;

    const vec4 blue = vec4(166, 202, 240, 255) / 255;
    const vec4 biruz = vec4(123, 228, 209, 255) / 255;
    const vec4 red = vec4(255, 0, 0, 255) / 255;
    const vec4 green = vec4(0, 255, 0, 255) / 255;
    const vec4 black = vec4(0, 0, 0, 255) / 255;
     
    
    const float kThreshold0 = 0.0;
    const float kThreshold1 = 0.1;
    const float kThreshold2 = 0.15;
    const float kThreshold3 = 1;

    if (k < kThreshold1)
    {
       color = linearExtrapolation(biruz, blue, kThreshold0, kThreshold1, k);
    }
    else if (k < kThreshold2)
    {
       color = linearExtrapolation(red, green, kThreshold1, kThreshold2, k);
    }
    else if (k < kThreshold3)
    {
       color = linearExtrapolation(biruz, black, kThreshold2, kThreshold3, k);
    }

    else
    {
       color = black;  
    }
  }
  
  )";
}
