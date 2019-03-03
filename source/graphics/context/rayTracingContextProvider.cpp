#include "rayTracingContextProvider.h"
#include "observables/inputEventObservable.h"
#include "GLSL/GLSLProgramRayTracing.h"
#include "model/model.h"
#include "model/modelInitializator.h"
#include "tools/sceneRotatingTool.h"

RayTracingContextProvider::RayTracingContextProvider(SDL_Window& window,
  InputEventObservable& inputEventObservable): ContextProvider(inputEventObservable)
{
  model_ = ModelInitializator::ConstructModel();
  auto rayTracingProgram = std::make_unique<GLSLProgramRayTracing>(window, *model_);
  sceneRotatingTool_ = std::make_unique<SceneRotatingTool>(*rayTracingProgram, inputEventObservable);
  GLSLProgram_ = std::move(rayTracingProgram);
  init();
}

RayTracingContextProvider::~RayTracingContextProvider() = default;
