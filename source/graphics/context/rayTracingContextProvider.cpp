#include "rayTracingContextProvider.h"
#include "observables/inputEventObservable.h"
#include "GLSL/GLSLProgramRayTracing.h"

RayTracingContextProvider::RayTracingContextProvider(SDL_Window& window,
  InputEventObservable& inputEventObservable): ContextProvider(inputEventObservable)
{
  glslProgram_ = std::make_unique<GLSLProgramRayTracing>(window);
  init();
}