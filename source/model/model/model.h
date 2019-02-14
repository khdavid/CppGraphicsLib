#pragma once
#include <memory>
#include <vector>
#include "object/object.h"

class Model
{
public:
  void setObject(std::unique_ptr<Object> object);
private:
  std::vector<std::unique_ptr<Object>> objects_;
};

