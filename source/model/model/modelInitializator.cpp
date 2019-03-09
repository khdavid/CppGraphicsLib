#include "modelInitializator.h"
#include "object/objectsFactory.h"
#include "materials/materialsFactory.h"
#include "geometryObjects/sphere.h"

namespace ModelInitializator
{
std::unique_ptr<Model> ConstructModel()
{
  std::unique_ptr<Model> model = std::make_unique<Model>();
  
  model->setObject(
    ObjectsFactory::createSphereObject(MaterialsFactory::RedDiffuse(),
    Sphere{ Point3D(250, 200, 500), 100 }));

  model->setObject(
    ObjectsFactory::createSphereObject(MaterialsFactory::RedDiffuse(),
      Sphere{ Point3D(450, 200, 480), 150 }));

  model->setObject(
    ObjectsFactory::createSphereObject(MaterialsFactory::RedDiffuse(),
      Sphere{ Point3D(450, 300, 580), 150 }));

  return model;
}
}
