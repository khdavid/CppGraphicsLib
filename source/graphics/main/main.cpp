#include <iostream>

#include "eventHandlers/mainLoop.h"
#include "geometryObjects/point.h"
#include "geometryObjects/vector.h"
#include "geometryObjects/triangle.h"
#include "geometryObjects/matrix.h"
#include "commands/GLSLProgramsManager.h"
#include <vector>
#include "context/rayTracingContextProvider.h"


void test()
{
  Vector2D tv(7);
  Vector<double, 4> aaa{ 1.0,2.0 };
  IndexAccessor<double, 4> aaab;
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

  Matrix<double, 2> m {1,2,3};
  Vector2D a1, a2, a3;
  a1 = a2 = a3;
  Matrix2D m2 = { 1.2344353453453534,2e-5,3 };
  Matrix3D m3d = { 1.2344353453453534,2e-5,3 };
  Vector3D v3d = { 1.2344353453453534,2e-5,3 };
  auto res = m3d * v3d;

  m2 + 2 * m2 * 2 * 2 / 2;
  -m2;
  m2 - m2;
  Matrix2D m3 = { 3,4,5 };
  Matrix2D m4 = m2 * m3;

  Vector3D v1, v2;
  double n1 = v1 * v2; n1;



}
int main(int, char**)
{
  test();
  RayTracingContextProvider contextProvider;
  MainLoop(contextProvider).run();
  std::unique_ptr<GLSLProgramsManager> programManager_;
  return 0;
}
