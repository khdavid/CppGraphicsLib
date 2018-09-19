#include "sdl2/sdl.h"
#include <iostream>
#include <OpenGl/gl.h>

#include "mainLoop.hpp"


int main()
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
  MainLoop().run();
  return 0;
}
