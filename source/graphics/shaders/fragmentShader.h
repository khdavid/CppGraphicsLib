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

void main()
{
  color = vec4(gl_FragCoord.x/ 640, 1 - gl_FragCoord.y / 480, gl_FragCoord.x/ 640, sin(gl_FragCoord.y / 10) );
}

)";