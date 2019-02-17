#include "rayTracingContextProvider.h"
#include "commands/GLSLProgramsManager.h"
#include "wrappers/SDL_WindowWrapper.h"
#include "observables/inputEventObservable.h"



RayTracingContextProvider::RayTracingContextProvider()
{
  spriteManager_ = std::make_unique<GLSLProgramsManager>(*window_->getNative(), *inputEventObservable_);
}
