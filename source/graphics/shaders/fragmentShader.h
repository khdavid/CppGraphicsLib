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


void main()
{
  color.xyz = varyingColor.rgb * fade * 20;
  color.w = 0.6f;
}

)";