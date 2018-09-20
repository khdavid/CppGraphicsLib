//
//  contextBuilder.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#include <iostream>

#include <sdl2/sdl.h>

#include "contextProvider.hpp"
#include "contextBuilder.hpp"

ContextBuilder::ContextBuilder(ContextProvider& contextProvider):
  contextProvider_(contextProvider)
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindow(
    "",                         // window title
    SDL_WINDOWPOS_CENTERED,     // x position, centered
    SDL_WINDOWPOS_CENTERED,     // y position, centered
    640,                        // width, in pixels
    480,                        // height, in pixels
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);        // flags
  
  std::cout << "Windows in initialized...";

  mouseEventLogger_ = std::make_unique<MouseEventLogger>();
  contextProvider_.getMouseEventObservable_().addMouseListener(mouseEventLogger_.get());
}
