// Alexandrescu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
namespace
{
size_t gWidgetName = 0;

class Widget
{
public:
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
class OpNewCreator
{
public:
  static T* Create()
  {
    return new(T);
  }
protected:
  ~OpNewCreator() = default;
};

template<class T>
class MallocCreator
{
public:
  static T* Create()
  {
    auto buf = std::malloc(sizeof(T));
    auto address = new(buf) T;
    return address;
  }
protected:
  ~MallocCreator() = default;
};

template<class T>
class PrototypeCreator
{
public:
  PrototypeCreator(T* obj = nullptr): prototype_(obj)
  {
    std::cout << "Constructor: PrototypeCreator" << std::endl;
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
protected:
  ~PrototypeCreator() = default;

private:

  T* prototype_;
};


template <template <class> class CreationPolicy> 
class WidgetManager : public CreationPolicy<Widget>
{
public:
  static void foo()
  {
    std::cout << "foo" << std::endl;
  }
}; 





}

void oldTests()
{
  OpNewCreator<int>::Create();
  MallocCreator<int>::Create();
  auto object1 = MallocCreator<Widget>::Create();
  auto object2 = OpNewCreator<Widget>::Create();


  WidgetManager<MallocCreator>::Create();
  WidgetManager<MallocCreator>::foo(); 
  auto widgetManager = new(WidgetManager<PrototypeCreator>);

}

int main()
{

}

