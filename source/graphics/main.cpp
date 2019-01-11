#include <iostream>

#include "contextProvider.h"
#include "eventHandlers/mainLoop.h"
#include "geometryObjects/point.h"
#include "geometryObjects/triangle.h"

void test()
{
  int tt[33];
  std::array<int, 4> rr = { 23, 3, 4, 5 };

  auto aa = sizeof(tt);
  int x = 5;
}

int main(int argc, char** argv)
{
  
  test();
  ContextProvider contextProvider;
  MainLoop(contextProvider).run();
  return 0;
}
