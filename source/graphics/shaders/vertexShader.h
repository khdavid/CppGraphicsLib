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

in vec3 vertexPosition;
in vec3 vertexColor;
varying vec3 varyingColor;
uniform float fade;


void main()
{
  gl_Position.x = vertexPosition[0];
  gl_Position.y = vertexPosition[1];
  gl_Position.z = vertexPosition[2];
  gl_Position.w = 1.0;

  varyingColor = vertexColor;
}

)";