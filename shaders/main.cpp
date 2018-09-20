#include "sdl2/sdl.h"
#include <iostream>
#include <OpenGl/gl.h>

#include "contextProvider.hpp"
#include "contextBuilder.hpp"
#include "mainLoop.hpp"


int main()
{
  ContextProvider contextProvider;
  ContextBuilder contextBuilder(contextProvider);
  MainLoop(contextProvider).run();
  return 0;
}
