#include <iostream>

#include "eventHandlers/mainLoop.h"
#include "geometryObjects/point.h"
#include "geometryObjects/vector.h"
#include "geometryObjects/matrix.h"
#include "context/rayTracingContextProvider.h"
#include "context/contextManager.h"
#include <typeinfo>
#include "utils/geometryUtils.h"

namespace
{
void test()
{
  Matrix3D m = { 1, 2, 3, 4 , 3,5,7,9 };

  auto x = GeometryUtils::det(m); x;
  x = 7;
}
}
int main(int, char**)
{
  test();
  ContextManager contextManager;
  MainLoop(contextManager).run();
  return 0;
}
