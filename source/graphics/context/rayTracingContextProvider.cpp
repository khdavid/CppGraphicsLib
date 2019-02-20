#include "rayTracingContextProvider.h"
#include "observables/inputEventObservable.h"
#include "GLSL/GLSLProgramRayTracing.h"
#include "model/model.h"
#include "model/modelInitializator.h"

RayTracingContextProvider::RayTracingContextProvider(SDL_Window& window,
  InputEventObservable& inputEventObservable): ContextProvider(inputEventObservable)
{
  model_ = ModelInitializator::ConstructModel();
  glslProgram_ = std::make_unique<GLSLProgramRayTracing>(window);
  init();
}

RayTracingContextProvider::~RayTracingContextProvider() = default;
