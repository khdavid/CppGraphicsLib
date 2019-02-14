#include <memory>

#include "materials/material.h"
#include "geometryObjects/sphere.h"
#include "objectsFactory.h"


std::unique_ptr<SphereObject> ObjectsFactory::createSphereObject(
  Material material, Sphere sphere)
{
  return std::make_unique<SphereObject>(std::move(material), std::move(sphere));
}
