#include "object/object.h"
#include "model.h"

void Model::setObject(std::unique_ptr<Object> object)
{
  objects_.push_back(std::move(object));
}
