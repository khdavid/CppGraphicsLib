#pragma once
#include "listeners/inputEventListener.h"

class GLSLProgramRayTracing;
class InputEventObservable;

class Tool : public InputEventListener
{
public:
  Tool(GLSLProgramRayTracing& rayTracingProgram, InputEventObservable& inputEventObservable);
  ~Tool();
protected:
  GLSLProgramRayTracing& rayTracingProgram_;
  InputEventObservable& inputEventObservable_;
};

