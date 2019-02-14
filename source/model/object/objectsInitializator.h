#pragma once

#include "model/model.h"

class ObjectsInitializator
{
public:
  ObjectsInitializator();
  const Model& getModel() const;
private:
  Model objectsManager_;
};

