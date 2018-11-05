#include <iostream>

#include "contextProvider.hpp"
#include "eventHandlers/mainLoop.hpp"

#undef main
int main()
{
  ContextProvider contextProvider;
  MainLoop(contextProvider).run();
  return 0;
}
