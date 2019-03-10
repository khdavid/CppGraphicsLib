#include "GLSL/GLSLProgramRayTracing.h"
#include "observables/inputEventObservable.h"

#include "tool.h"

Tool::Tool(
  GLSLProgramRayTracing& rayTracingProgram,
  InputEventObservable& inputEventObservable) :
  rayTracingProgram_(rayTracingProgram),
  inputEventObservable_(inputEventObservable)
{
  inputEventObservable_.addInputListener(this);
}

Tool::~Tool()
{
  inputEventObservable_.removeInputListener(this);
}
