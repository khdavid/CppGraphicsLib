#include "sphereObject.h"

SphereObject::SphereObject(Material material, Sphere sphere) : 
  sphere_(std::move(sphere)),
  Object(material)
{
}