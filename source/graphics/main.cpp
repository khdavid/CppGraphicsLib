#include <iostream>

#include "contextProvider.h"
#include "eventHandlers/mainLoop.h"
#include "geometryObjects/point2D.h"


int main(int argc, char** argv)
{
  
  Point2D aa(1, 2);
  auto bb = aa;
  bb[0] = 10;
  ContextProvider contextProvider;
  MainLoop(contextProvider).run();
  return 0;
}
