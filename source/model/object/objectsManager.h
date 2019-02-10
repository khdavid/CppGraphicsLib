#pragma once
#include <memory>
#include <vector>

class Object;

class ObjectsManager
{
public:
  void setObject(std::unique_ptr<Object> object);
private:
  std::vector<std::unique_ptr<Object>> objects_;
};

