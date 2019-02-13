#pragma once

#include "geometryObjects/sphere.h"
#include "object.h"

class SphereObject : public Object
{
public:
  SphereObject(Material material, Sphere sphere);
private:
  Sphere sphere_;
};

