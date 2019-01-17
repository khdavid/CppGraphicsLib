#include "geometryObjects/vector.h"
#include "geometryObjects/point.h"
#include "operations.h"

Vector2D operator-(const Point2D& first, const Point2D& second)
{
  return Vector2D{ first[0] - second[0], first[1] - second[1] };
}

Vector3D operator-(const Point3D& first, const Point3D& second)
{
  return Vector3D{ first[0] - second[0], first[1] - second[1], first[2] - second[2]};
}

int numb()
{
  return 0;
}
void test2()
{
  Vector<4> aaa{ 1.0, 2.0, 3.0,4.0 };
  Vector<4> bbb{ 1.0, 2, 3, 4 };
  const int x = 2;
  Vector<4> abc{ x,x,x,numb() };
  Vector<4> ddd;

  IndexAccessor<Point2D, 2> tr ( Point2D{1,2},Point2D{1,3} );
  auto ccc = aaa;

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
