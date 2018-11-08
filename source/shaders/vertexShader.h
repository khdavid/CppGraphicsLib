//
//  vertexShader.h
//  shaders
//
//  Created by David Khudaverdyan on 28/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef vertexShader_hpp
#define vertexShader_hpp

#include <stdio.h>

const std::string shaper = R"(
#version 130

in vec2 vertexPosition;

void main
{
  gl_Position.xy = vertexPosition
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;
}

)";


#endif /* vertexShader_hpp */
