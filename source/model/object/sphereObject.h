#pragma once

#include "geometryObjects/sphere.h"
#include "object.h"

class SphereObject : public Object
{
public:
  SphereObject(Material material, Sphere sphere);
  const Sphere& getSphere() const;
  Sphere& getSphere();
private:
  Sphere sphere_;
};

