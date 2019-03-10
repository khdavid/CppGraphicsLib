#include "GLSL/GLSLProgramRayTracing.h"
#include "observables/inputEventObservable.h"
#include "objectsMovingTool.h"
#include "model/model.h"


ObjectsMovingTool::ObjectsMovingTool(
  GLSLProgramRayTracing& rayTracingProgram, 
  InputEventObservable& inputEventObservable,
  Model& model):
  Tool(rayTracingProgram, inputEventObservable),
  model_(model)
{
}

void ObjectsMovingTool::onMouseClick(int, int)
{
  int x = 5; x;
}

void ObjectsMovingTool::onMouseMove(int, int)
{
}
