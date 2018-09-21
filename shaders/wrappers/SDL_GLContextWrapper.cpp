//
//  SDLGLContextWrapper.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include "opengl/gl.h"

#include "SDL_GLContextWrapper.hpp"

 SDL_GLContextWrapper::SDL_GLContextWrapper(SDL_Window* window)
 {
   SDLGLContext_ = SDL_GL_CreateContext(window);
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

 SDL_GLContextWrapper::~SDL_GLContextWrapper()
 {
  SDL_GL_DeleteContext(SDLGLContext_);
 }


