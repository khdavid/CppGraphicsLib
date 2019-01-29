//
//  inputEventLogger.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <iostream>

#include "inputEventLogger.h"

void InputEventLogger::onKeyPress(SDL_Keycode keyCode)
{
  std::cout << "key press: " << keyCode << std::endl;
}

void InputEventLogger::onMouseClick(int x, int y)
{
  std::cout << "mouse click: " << x << " " << y << std::endl;
}

void InputEventLogger::onMouseRelease(int x, int y)
{
  std::cout << "mouse release: " << x << " " << y << std::endl;
}

void InputEventLogger::onMouseMove(int x, int y)
{
  std::cout << "mouse move: " << x << " " << y << std::endl;
}


void InputEventLogger::onMouseMovePassive(int x, int y)
{
  std::cout << "mouse move passive: " << x << " " << y << std::endl;
}

