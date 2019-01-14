#include <iostream>

#include "contextProvider.h"
#include "eventHandlers/mainLoop.h"
#include "geometryObjects/point.h"
#include "geometryObjects/vector.h"
#include "geometryObjects/triangle.h"
#include "geometryObjects/matrix.h"

#include <initializer_list>
#include <vector>


struct BaseTestClass
{
};

struct TestClass : BaseTestClass
{
  template<typename ...E>
  TestClass(E&&...e)
  {
    v_ = { double(std::forward<E>(e))... };
    std::initializer_list<double> list = { double(std::forward<E>(e))... };
    std::initializer_list<int> list2 = { 2,3,4};
    list.begin();
    list.end();
    list.size();
      arr_ = { double(std::forward<E>(e))... };
    v_[1] = 3;
    auto size = v_.size();

  }
  std::vector<double> v_;
  std::array<double, 3> arr_;
};

void test()
{
  Vector2D tv(7);
  Vector<4> aaa{ 1.0,2.0 };
  IndexAccessor<double, 4> aaab;
  TestClass tClass{2,3,4};
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

  Matrix<double, 2> m;
  

}

int main(int argc, char** argv)
{
  
  test();
  ContextProvider contextProvider;
  MainLoop(contextProvider).run();
  return 0;
}
