//
//  SDLGLContextWrapper.h
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <sdl.h>


struct SDL_Window;

class SDL_GLContextWrapper
{
public:
  SDL_GLContextWrapper(SDL_Window* window);
  ~SDL_GLContextWrapper();
  SDL_GLContextWrapper(const SDL_GLContextWrapper&) = delete;
  SDL_GLContextWrapper& operator=(const SDL_GLContextWrapper&) = delete;
private:
  SDL_GLContext SDLGLContext_;
  
};