#include <iostream>

#include "contextProvider.h"
#include "eventHandlers/mainLoop.h"
#include "geometryObjects/point2D.h"
#include "geometryObjects/triangle2D.h"


int main(int argc, char** argv)
{
  
  const Vector2D aa(1, 2);
  auto bb = aa * aa*aa / 7;
  bb[0] = 10;
  auto cc = 2 * bb * 2;
  auto tt = Point2D(1, 2);
  auto ttt = Triangle2D(tt, tt, tt);
  ContextProvider contextProvider;
  MainLoop(contextProvider).run();
  return 0;
}
