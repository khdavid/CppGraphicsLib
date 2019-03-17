#include "object/object.h"
#include "model.h"

namespace
{
template<class T>
std::vector<T> getSphereObjects(const std::vector<std::unique_ptr<Object>>& objects)
{
  std::vector<T> result;
  for (const auto& object : objects)
  {
    auto sphereObject = dynamic_cast<T>(object.get());
    if (sphereObject)
    {
      result.push_back(sphereObject);
    }
  }
  return result;
}

}
void Model::setObject(std::unique_ptr<Object> object)
{
  objects_.push_back(std::move(object));
}

std::vector<SphereObject *> Model::getSphereObjects()
{
  return ::getSphereObjects<SphereObject *>(objects_);
}

std::vector<const SphereObject*> Model::getSphereObjects() const
{
  return ::getSphereObjects<const SphereObject *>(objects_);
}
