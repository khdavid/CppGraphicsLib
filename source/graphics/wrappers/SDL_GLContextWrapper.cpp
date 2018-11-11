//
//  SDLGLContextWrapper.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <glew.h>
#include <iostream>

#include "SDL_GLContextWrapper.h"

 SDL_GLContextWrapper::SDL_GLContextWrapper(SDL_Window* window)
 {
   SDLGLContext_ = SDL_GL_CreateContext(window);
   auto errorCode = glewInit();
   if (errorCode != GLEW_OK)
   {
     std::cout << "Can't init glew" << std::endl;
   }

 }

 SDL_GLContextWrapper::~SDL_GLContextWrapper()
 {
  SDL_GL_DeleteContext(SDLGLContext_);
 }


