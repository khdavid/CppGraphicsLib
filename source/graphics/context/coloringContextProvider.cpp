#include "coloringContextProvider.h"
#include "observables/inputEventObservable.h"
#include "GLSL/GLSLProgramColoring.h"

ColoringContextProvider::ColoringContextProvider(SDL_Window& window,
  InputEventObservable& inputEventObservable) : ContextProvider(inputEventObservable)
{
  GLSLProgram_ = std::make_unique<GLSLProgramColoring>(window);
  init();
}