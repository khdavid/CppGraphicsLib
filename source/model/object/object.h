#pragma once
#include "materials/material.h"

class Object
{
public:
  Object(Material material);
private:
  Material material_;
};

