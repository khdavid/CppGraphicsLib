//
//  mouseEventLogger.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <iostream>

#include "mouseEventLogger.hpp"

void MouseEventLogger::onMouseClick()
{
  std::cout << "mouse click" << std::endl;
}

void MouseEventLogger::onMouseRelease()
{
  std::cout << "mouse release" << std::endl;
}

void MouseEventLogger::onMouseMove(int x, int y)
{
  std::cout << "mouse move: " << x << " " << y << std::endl;
}


void MouseEventLogger::onMouseMovePassive(int x, int y)
{
  std::cout << "mouse move passive: " << x << " " << y << std::endl;
}

