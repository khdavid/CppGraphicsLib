#include <vector>
#include <iostream>

#include "GLSL/GLObjects.h"
#include "utils/SDLUtils.h"
#include "GLSLProgramMandelbrot.h"


namespace
{
  const char* cFadeName = "fade";
  const char* cXShift = "xShift";
  const char* cYShift = "yShift";
}

void GLSLProgramMandelbrot::init()
{
  GLSLProgramFragmentShader::init();
  fadeUniform_ = glGetUniformLocation(programId_, cFadeName);
  xShiftUniform_ = glGetUniformLocation(programId_, cXShift);
  yShiftUniform_ = glGetUniformLocation(programId_, cYShift);

  glUniform1d(fadeUniform_, fade_);
  glUniform1d(xShiftUniform_, xShift_);
  glUniform1d(yShiftUniform_, yShift_);

}

void GLSLProgramMandelbrot::onMouseClick(int x, int y)
{
  xPrev_ = x;
  yPrev_ = y;
  render();
}

void GLSLProgramMandelbrot::onMouseMove(int x, int y)
{
  xShift_ += (x - xPrev_);
  yShift_ += -(y - yPrev_);
  xPrev_ = x;
  yPrev_ = y;
  
  glUniform1d(xShiftUniform_, xShift_);
  glUniform1d(yShiftUniform_, yShift_);
  render();
}

void GLSLProgramMandelbrot::onMouseScrolling(double velocity)
{
  auto mouseCoord = SDLUtils::getMouseXY();
  auto x = mouseCoord.first;
  auto y = mouseCoord.second;
  std::cout << "scrolling " << "x " << mouseCoord.first << "y " << mouseCoord.second << std::endl;
  
  auto sizes = SDLUtils::getScreenSizes();
  y = sizes.second - y;

  auto fadeOld = fade_;

  auto alpha = std::max(-0.5, velocity / 20.0);
  fade_ *= (1 + alpha);

  xShift_ = x - (x - xShift_) * fadeOld / fade_;
  yShift_ = y - (y - yShift_) * fadeOld / fade_;

  glUniform1d(fadeUniform_, fade_);
  glUniform1d(xShiftUniform_, xShift_);
  glUniform1d(yShiftUniform_, yShift_);
  std::cout << "fade: " << fade_ << std::endl;

  render();
}

std::string GLSLProgramMandelbrot::getFragmentShaderCode_() const
{
  return R"(

  #version 400
  
  out vec4 color;
  uniform double fade;
  uniform double xShift;
  uniform double yShift;


  struct ComplexNumber
  {
    double Real;
    double Imagine;
  };

  struct ComplexNumberFast
  {
    float Real;
    float Imagine;
  };
  
  ComplexNumber Product(in ComplexNumber first, in ComplexNumber second)
  {
    ComplexNumber result;  
    result.Real = first.Real * second.Real - first.Imagine * second.Imagine;
    result.Imagine = first.Real * second.Imagine + first.Imagine * second.Real;
    return result;
  }
  
  ComplexNumberFast Product(in ComplexNumberFast first, in ComplexNumberFast second)
  {
    ComplexNumberFast result;  
    result.Real = first.Real * second.Real - first.Imagine * second.Imagine;
    result.Imagine = first.Real * second.Imagine + first.Imagine * second.Real;
    return result;
  }

  ComplexNumber Add(in ComplexNumber first, in ComplexNumber second)
  {
    ComplexNumber result;  
    result.Real = first.Real + second.Real;
    result.Imagine = first.Imagine + second.Imagine;
    return result;
  }
  
  ComplexNumberFast Add(in ComplexNumberFast first, in ComplexNumberFast second)
  {
    ComplexNumberFast result;  
    result.Real = first.Real + second.Real;
    result.Imagine = first.Imagine + second.Imagine;
    return result;
  }

  double length2(in ComplexNumber number)
  {
     return number.Real * number.Real + number.Imagine * number.Imagine;
  }

  float length2(in ComplexNumberFast number)
  {
     return number.Real * number.Real + number.Imagine * number.Imagine;
  }
  
  vec4 linearExtrapolation(const vec4 first, const vec4 last, float min, float max, float x)
  {
    return first + (x - min) * (last - first) / (max - min);
  }
  
  int getOutOfBoundsIdx(int nMax)
  {
    ComplexNumber z;
    z.Real = 0;
    z.Imagine = 0;
  
    ComplexNumber c;
    c.Real = (gl_FragCoord.x - xShift ) * fade;
    c.Imagine = (gl_FragCoord.y - yShift) * fade; 

    int i = 0;

    for (i = 0; i < nMax; i++)
    {
       z = Add (Product(z,z), c);
       if (length2(z) > 4) break;
    }
    
    return i;
  } 

  int getOutOfBoundsIdxFast(int nMax)
  {
    ComplexNumberFast z;
    z.Real = 0;
    z.Imagine = 0;
  
    ComplexNumberFast c;
    c.Real = float((gl_FragCoord.x - xShift ) * fade);
    c.Imagine = float((gl_FragCoord.y - yShift) * fade); 

    int i = 0;

    for (i = 0; i < nMax; i++)
    {
       z = Add (Product(z,z), c);
       if (length2(z) > 4) break;
    }
    
    return i;
  } 

  
  void main()
  {

    const vec4 blue = vec4(166, 202, 240, 255) / 255;
    const vec4 biruz = vec4(123, 228, 209, 255) / 255;
    const vec4 red = vec4(255, 0, 0, 255) / 255;
    const vec4 green = vec4(0, 255, 0, 255) / 255;
    const vec4 black = vec4(0, 0, 0, 255) / 255;
     
    
    const int nMaxFloatMode = 1000;
    const int nMaxDoubleMode = 400;

    const float kThreshold0 = 0.0;
    const float kThreshold1 = 100;
    const float kThreshold2 = 150;
    const float kThreshold3 = 250;
    const float kThreshold4 = 390;
    

    const float fadeThreshold = 1e-7;

    float k = 0;
    if (fade > fadeThreshold)
    {
      k = getOutOfBoundsIdxFast(nMaxFloatMode);
    }
    else
    {
       k = getOutOfBoundsIdx(nMaxDoubleMode);
    }

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
       color = linearExtrapolation(biruz, blue, kThreshold2, kThreshold3, k);
    }
    else if (k < kThreshold4)
    {
       color = linearExtrapolation(biruz, green, kThreshold3, kThreshold4, k);
    }

    else
    {
       color = black;  
    }
  }
  
  )";
}
