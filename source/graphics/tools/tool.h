#pragma once
#include "listeners/inputEventListener.h"

class GLSLProgramRayTracing;
class InputEventObservable;
class Model;

class Tool : public InputEventListener
{
public:
  Tool(GLSLProgramRayTracing& rayTracingProgram, 
    InputEventObservable& inputEventObservable,
    Model& model);
  ~Tool();
protected:
  GLSLProgramRayTracing& rayTracingProgram_;
  InputEventObservable& inputEventObservable_;
  Model& model_;
};

