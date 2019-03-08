#include "object/object.h"
#include "model.h"

void Model::setObject(std::unique_ptr<Object> object)
{
  objects_.push_back(std::move(object));
}

std::vector<SphereObject *> Model::getSphereObjects()
{
  std::vector<const SphereObject*> objects = static_cast<const Model *>(this)->getSphereObjects();
  std::vector<SphereObject*> result(objects.size());
  for (const auto &object : objects)
  {
    result.push_back(const_cast<SphereObject*>(object));
  }
  return result;
}

std::vector<const SphereObject*> Model::getSphereObjects() const
{
  std::vector<const SphereObject *> result;
  for (const auto& object : objects_)
  {
    auto sphereObject = dynamic_cast<const SphereObject *>(object.get());
    if (sphereObject)
    {
      result.push_back(sphereObject);
    }
  }
  return result;

}
