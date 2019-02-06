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

}// end of namespacde GeometryUtils