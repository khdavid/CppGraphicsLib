// Alexandrescu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
namespace
{
size_t gWidgetName = 0;

struct Widget
{

  Widget()
  {
    std::cout << name << ": widget constructed" << std::endl;
  }
  ~Widget()
  {
    std::cout << name << ": widget destructeed" << std::endl;
  }
  Widget* Clone()
  {
    std::cout << name << ": somebody just cloned me" << std::endl;
    return new(Widget);
  }
private:
  std::string name = std::to_string(gWidgetName++);
};

template<class T>
struct OpNewCreator
{
  static T* Create()
  {
    return new(T);
  }
};

template<class T>
struct MallocCreator
{
  static T* Create()
  {
    auto buf = std::malloc(sizeof(T));
    auto address = new(buf) T;
    return address;
  }
};

template<class T>
struct PrototypeCreator
{
  PrototypeCreator(T* obj = nullptr): prototype_(obj)
  {

  }
  T* Create()
  {
    return prototype_ ? prototype_->Clone() : nullptr;
  }
  void SetPrototype(T* pObj)
  {
    prototype_ = pObj;
  }
  T* GetPrototype()
  {
    return prototype_;
  }

private:
  T* prototype_;
};


}
int main()
{
  OpNewCreator<int>::Create();
  MallocCreator<int>::Create();
  auto object1 = MallocCreator<Widget>::Create();
  auto object2 = OpNewCreator<Widget>::Create();
  auto object3 = PrototypeCreator<Widget>(&Widget()).Create();
}

