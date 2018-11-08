//
//  SDLWindowWrapper.h
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <stdio.h>  

struct SDL_Window;

class SDL_WindowWrapper
{
public:
  SDL_WindowWrapper();
  ~SDL_WindowWrapper();
  SDL_WindowWrapper(const SDL_WindowWrapper&) = delete;
  SDL_WindowWrapper& operator=(const SDL_WindowWrapper&) = delete;
  SDL_Window* getNative();
  const SDL_Window* getNative() const;

private:
  SDL_Window* SDLWindow_ = nullptr;
};
