#include "objectsInitializator.h"
#include "objectsFactory.h"
#include "materials/materialsFactory.h"
#include "geometryObjects/sphere.h"


ObjectsInitializator::ObjectsInitializator()
{
  Sphere sphere{ Point3D(200, 200, 200), 100 };
  objectsManager_.setObject(ObjectsFactory::createSphereObject(MaterialsFactory::RedDiffuse(), sphere));
}

const Model & ObjectsInitializator::getObjectManager() const
{
  return objectsManager_;
}
