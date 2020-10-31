// Alexandrescu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

namespace
{

class Widget
{
public:  
  Widget()
  {
    std::cout << "Widget constructed" << std::endl;
  }
  ~Widget()
  {
    std::cout << "Widget destructeed" << std::endl;
  }

};

template<class T>
class OpNewCreator
{
public:
  static T* Create()
  {
    return new(T);
  }
};

template<class T>
class OpMallocCreator
{
public:
  static T* Create()
  {
    auto buf = std::malloc(sizeof(T));
    auto address = new(buf) T;
    return address;
  }
};

}
int main()
{
  OpNewCreator<int>::Create();
  OpMallocCreator<int>::Create();
  //auto object = OpMallocCreator<Widget>::Create();
  auto object = OpNewCreator<Widget>::Create();
  free(object);
  delete(object);

}

