#pragma once
#include <memory>
#include "contextProvider.h"

class GLSLProgramsManager;
class InputEventObservable;
class SDL_WindowWrapper;

class RayTracingContextProvider : public ContextProvider
{
public:
  RayTracingContextProvider(SDL_WindowWrapper& window, InputEventObservable& inputEventObservable);
  ~RayTracingContextProvider();
private:
  std::unique_ptr<GLSLProgramsManager> programManager_;

};

