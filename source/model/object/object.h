#pragma once
#include "materials/material.h"

class Object
{
public:
  Object(Material material);
  Material getMaterial() const;

  virtual ~Object() = default;
private:
  Material material_;
};

