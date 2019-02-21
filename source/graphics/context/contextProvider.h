#pragma once
#include <memory>

class GLSLProgramBase;
class InputEventObservable;

class ContextProvider
{
public:
  ContextProvider(InputEventObservable& inputEventObservable);
  virtual ~ContextProvider();
  void init();
protected:
  std::unique_ptr<GLSLProgramBase> GLSLProgram_;
  InputEventObservable& inputEventObservable_;

};

