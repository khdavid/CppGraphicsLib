#pragma once

#include "model/model.h"

class ObjectsInitializator
{
public:
  ObjectsInitializator();
  const Model& getObjectManager() const;
private:
  Model objectsManager_;
};

