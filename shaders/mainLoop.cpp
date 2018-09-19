//
//  mainLoop.cpp
//  shaders
//
//  Created by David Khudaverdyan on 17/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#include <sdl2/sdl.h>

#include "mainLoop.hpp"

void MainLoop::run()
{
  SDL_Event event;
  
  bool quit = false;
  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }
}





