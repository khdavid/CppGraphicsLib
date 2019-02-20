#pragma once
#include <sdl.h>
#include "contextProvider.h"

class InputEventObservable;

class ColoringContextProvider : public ContextProvider
{
public:
  ColoringContextProvider(SDL_Window& window, InputEventObservable& inputEventObservable);
};

