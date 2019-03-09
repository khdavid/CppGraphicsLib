#pragma once

#include "geometryObjects/sphere.h"
#include "object.h"

class SphereObject : public Object
{
public:
  SphereObject(Material material, Sphere sphere);
  Sphere getSphere() const;
private:
  Sphere sphere_;
};

