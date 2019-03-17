#include "GLSL/GLSLProgramRayTracing.h"
#include "observables/inputEventObservable.h"

#include "tool.h"

Tool::Tool(
  GLSLProgramRayTracing& rayTracingProgram,
  InputEventObservable& inputEventObservable,
  Model& model) :
  rayTracingProgram_(rayTracingProgram),
  inputEventObservable_(inputEventObservable),
  model_(model)
{
  inputEventObservable_.addInputListener(this);
}

Tool::~Tool()
{
  inputEventObservable_.removeInputListener(this);
}
