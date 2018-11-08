#include <iostream>

#include "contextProvider.h"
#include "eventHandlers/mainLoop.h"


int main(int argc, char** argv)
{
  ContextProvider contextProvider;
  MainLoop(contextProvider).run();
  return 0;
}
