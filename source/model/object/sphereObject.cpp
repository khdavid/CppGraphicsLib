#include "sphereObject.h"

SphereObject::SphereObject(Material material, Sphere sphere) : 
  sphere_(std::move(sphere)),
  Object(material)
{
}

const Sphere& SphereObject::getSphere() const
{
  return sphere_;
}

Sphere& SphereObject::getSphere()
{
  return sphere_;
}
