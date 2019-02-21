#include "contextProvider.h"
#include "GLSL/GLSLProgramBase.h"
#include "observables/inputEventObservable.h"

void ContextProvider::init()
{
  GLSLProgram_->init();
  inputEventObservable_.addInputListener(GLSLProgram_.get());

  int x = 0;
  int y = 0;
  SDL_GetMouseState(&x, &y);
  GLSLProgram_->onMouseMovePassive(x, y);
  GLSLProgram_->render();

}

ContextProvider::ContextProvider(InputEventObservable& inputEventObservable):
  inputEventObservable_(inputEventObservable)
{
}

ContextProvider::~ContextProvider()
{
  inputEventObservable_.removeInputListener(GLSLProgram_.get());
}
