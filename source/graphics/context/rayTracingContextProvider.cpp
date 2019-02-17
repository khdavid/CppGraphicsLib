#include "rayTracingContextProvider.h"
#include "commands/GLSLProgramsManager.h"
#include "wrappers/SDL_WindowWrapper.h"
#include "observables/inputEventObservable.h"
#include "wrappers/SDL_WindowWrapper.h"

RayTracingContextProvider::RayTracingContextProvider(SDL_WindowWrapper& window,
  InputEventObservable& inputEventObservable)
{
  programManager_ = std::make_unique<GLSLProgramsManager>(*window.getNative(), inputEventObservable);
}

RayTracingContextProvider::~RayTracingContextProvider()
{
}
