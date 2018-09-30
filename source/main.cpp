#include <iostream>

#include "contextProvider.hpp"
#include "mainLoop.hpp"


int main()
{
  ContextProvider contextProvider;
  MainLoop(contextProvider).run();
  return 0;
}
