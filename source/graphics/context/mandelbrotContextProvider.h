#pragma once
#include <sdl.h>
#include "contextProvider.h"

class InputEventObservable;

class MandelbrotContextProvider : public ContextProvider
{
public:
  MandelbrotContextProvider(SDL_Window& window, InputEventObservable& inputEventObservable);
};

