#pragma once
#include <sdl.h>
#include "contextProvider.h"

class InputEventObservable;

class RayTracingContextProvider : public ContextProvider
{
public:
  RayTracingContextProvider(SDL_Window& window, InputEventObservable& inputEventObservable);
};
