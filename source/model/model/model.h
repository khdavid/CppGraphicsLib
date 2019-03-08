#pragma once
#include <memory>
#include <vector>
#include "object/object.h"
#include "object/sphereObject.h"

class Model
{
public:
  void setObject(std::unique_ptr<Object> object);
  std::vector<SphereObject *> getSphereObjects();
  std::vector<const SphereObject *> getSphereObjects() const;

private:
  std::vector<std::unique_ptr<Object>> objects_;
}; 

