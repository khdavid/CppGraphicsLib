#include <iostream>

#include "eventHandlers/mainLoop.h"
#include "geometryObjects/point.h"
#include "geometryObjects/vector.h"
#include "geometryObjects/matrix.h"
#include "context/rayTracingContextProvider.h"
#include "context/contextManager.h"
#include <typeinfo>


int main(int, char**)
{
  ContextManager contextManager;
  MainLoop(contextManager).run();
  return 0;
}
