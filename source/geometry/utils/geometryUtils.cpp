#include "geometryObjects/matrix.h"

#include "geometryUtils.h"

namespace GeometryUtils
{

 Matrix4D createIdentityMatrix4D()
{
   Matrix4D result;
   for (int i = 0; i < 4; ++i)
   {
     result[i][i] = 1;
   }
   return result;
}

 Matrix4D createMatrix4D(const Matrix3D& rotation, const Vector3D& shift)
 {
   Matrix4D result = createIdentityMatrix4D();
   for (size_t i = 0; i < 3; ++i)
   {
     for (size_t j = 0; j < 3; ++j)
     {
       result[i][j] = rotation[i][j];
     }
   }

   for (size_t i = 0; i < 3; ++i)
   {
     result[i][3] = shift[i];
   }

   return result;
 }

 Matrix3D createRotation(const Vector3D & /*direction*/, double /*angle*/)
 {
   return Matrix3D();
 }

}// end of namespacde GeometryUtils
