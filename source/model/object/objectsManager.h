#pragma once
#include <memory>
#include <vector>
#include "object.h"

class ObjectsManager
{
public:
  void setObject(std::unique_ptr<Object> object);
private:
  std::vector<std::unique_ptr<Object>> objects_;
};

