//
//  fragmentShader.h
//  shaders
//
//  Created by David Khudaverdyan on 28/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <string>

const std::string cFragmentShaderCode = R"(
#version 130

out vec4 color;
varying vec3 varyingColor;
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
  //ComplexNumber z;
  //   z.Real = 0;
  //   z.Imagine = 0;

  //for (int i = 0; i < 100; i++)
  //{
  //   ComplexNumber c;
  //   c.Real = (gl_FragCoord.x - 320 ) / 640 * fade;
  //   c.Imagine = (gl_FragCoord.y -900) / 320 * fade; 
  //   z = Add (Product(Product(z,z),z), Product(c,c));
  //   if (length2(z) < 0.001) break;
  //   if (length2(z) > 100) break;
  //}
  //float len = length(z);
  //color = vec4(100 + len*len, sqrt(len), len, 1);
  color.xyz = varyingColor.rgb;
  color.w = 1;
}

)";