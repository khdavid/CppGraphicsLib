#pragma once
#include "materials/material.h"

class Object
{
public:
  Object(Material material);
  virtual ~Object() = default;
private:
  Material material_;
};

