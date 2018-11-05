//
//  SDLGLContextWrapper.hpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef SDLGLContextWrapper_hpp
#define SDLGLContextWrapper_hpp

#include <stdio.h>
#include <sdl.h>


class SDL_Window;

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

#endif /* SDLGLContextWrapper_hpp */
