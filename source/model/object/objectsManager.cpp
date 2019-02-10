#include "object.h"
#include "objectsManager.h"

void ObjectsManager::setObject(std::unique_ptr<Object> object)
{
  objects_.push_back(std::move(object));
}
