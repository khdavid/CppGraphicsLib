#include <iostream>

#include "contextProvider.h"
#include "eventHandlers/mainLoop.h"
#include "geometryObjects/point.h"
#include "geometryObjects/vector.h"
#include "geometryObjects/triangle.h"

void test()
{
  Vector3D zero;

  Vector3D aa(1, 2, 3);
  aa = aa + aa;
  aa = aa * 2;
  aa = 2 * aa;
  aa = -aa;
  aa = aa / 3;

  Point3D bb;
  bb + aa;


  Point2D cc;

  aa - aa;
  cc - cc;

}

int main(int argc, char** argv)
{
  
  test();
  ContextProvider contextProvider;
  MainLoop(contextProvider).run();
  return 0;
}
