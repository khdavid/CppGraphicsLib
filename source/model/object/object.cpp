#include <utility>
#include "object.h"

Object::Object(Material material):
  material_(std::move(material))
{
}

Material Object::getMaterial() const
{
  return material_;
}
