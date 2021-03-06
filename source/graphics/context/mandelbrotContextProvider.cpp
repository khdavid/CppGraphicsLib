#include "mandelbrotContextProvider.h"
#include "observables/inputEventObservable.h"
#include "GLSL/GLSLProgramMandelbrot.h"

MandelbrotContextProvider::MandelbrotContextProvider(SDL_Window& window,
  InputEventObservable& inputEventObservable) : ContextProvider(inputEventObservable)
{
  GLSLProgram_ = std::make_unique<GLSLProgramMandelbrot>(window);
  init();
}