#include "modelInitializator.h"
#include "object/objectsFactory.h"
#include "materials/materialsFactory.h"
#include "geometryObjects/sphere.h"

namespace ModelInitializator
{
std::unique_ptr<Model> ConstructModel()
{
  std::unique_ptr<Model> model = std::make_unique<Model>();
  Sphere sphere{ Point3D(200, 200, 200), 100 };
  model->setObject(ObjectsFactory::createSphereObject(MaterialsFactory::RedDiffuse(), sphere));
  return model;
}
}
