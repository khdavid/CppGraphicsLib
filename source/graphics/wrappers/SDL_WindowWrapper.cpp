//
//  SDLWindowWrapper.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#include <iostream>
#include <sdl.h>

#include "SDL_WindowWrapper.h"

SDL_WindowWrapper::SDL_WindowWrapper()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDLWindow_ = SDL_CreateWindow(
    "",                         // window title
    SDL_WINDOWPOS_CENTERED,     // x position, centered
    SDL_WINDOWPOS_CENTERED,     // y position, centered
    640,                        // width, in pixels
    480,                        // height, in pixels
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE); // flags

}

SDL_WindowWrapper::~SDL_WindowWrapper()
{
  SDL_DestroyWindow(SDLWindow_);
}

SDL_Window* SDL_WindowWrapper::getNative()
{
  return SDLWindow_;
}

const SDL_Window* SDL_WindowWrapper::getNative() const
{
  return SDLWindow_;
}

