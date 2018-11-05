#include <iostream>

#include "contextProvider.hpp"
#include "eventHandlers/mainLoop.hpp"


int main(int argc, char** argv)
{
  ContextProvider contextProvider;
  MainLoop(contextProvider).run();
  return 0;
}
