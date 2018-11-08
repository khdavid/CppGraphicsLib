//
//  mouseEventLogger.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <iostream>

#include "mouseEventLogger.h"

void MouseEventLogger::onMouseClick(int x, int y)
{
  std::cout << "mouse click: " << x << " " << y << std::endl;
}

void MouseEventLogger::onMouseRelease(int x, int y)
{
  std::cout << "mouse release: " << x << " " << y << std::endl;
}

void MouseEventLogger::onMouseMove(int x, int y)
{
  std::cout << "mouse move: " << x << " " << y << std::endl;
}


void MouseEventLogger::onMouseMovePassive(int x, int y)
{
  std::cout << "mouse move passive: " << x << " " << y << std::endl;
}

