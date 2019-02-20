#include "contextProvider.h"
#include "GLSL/GLSLProgramBase.h"
#include "observables/inputEventObservable.h"

void ContextProvider::init()
{
  glslProgram_->init();
  inputEventObservable_.addInputListener(glslProgram_.get());

  int x = 0;
  int y = 0;
  SDL_GetMouseState(&x, &y);
  glslProgram_->onMouseMovePassive(x, y);
  glslProgram_->render();

}

ContextProvider::ContextProvider(InputEventObservable& inputEventObservable):
  inputEventObservable_(inputEventObservable)
{
}

ContextProvider::~ContextProvider()
{
  inputEventObservable_.removeInputListener(glslProgram_.get());
}
