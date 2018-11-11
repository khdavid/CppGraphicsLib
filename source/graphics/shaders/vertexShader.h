//
//  vertexShader.h
//  shaders
//
//  Created by David Khudaverdyan on 28/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <string>

const std::string cVertexShaderCode = R"(
#version 130

in vec2 vertexPosition;

void main()
{
  gl_Position.xy = vertexPosition;
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;
}

)";