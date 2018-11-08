//
//  fragmentShader.h
//  shaders
//
//  Created by David Khudaverdyan on 28/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <stdio.h>

const std::string shaper = R"(
#version 130

out vec3 color;

void main
{
  color = vec3(1.0, 0.0, 0.0);
}

)";