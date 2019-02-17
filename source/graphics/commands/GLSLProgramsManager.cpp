#include <glew.h>

#include <iostream>
#include "observables/inputEventObservable.h"
#include "GLSL/GLSLProgramRayTracing.h"
#include "GLSL/GLSLProgramMandelbrot.h"
#include "commands/GLSLProgramsManager.h"

GLSLProgramsManager::GLSLProgramsManager(SDL_Window& window, InputEventObservable& inputEventObservable) :
  window_(window),
  inputEventObservable_(inputEventObservable)
{
  inputEventObservable_.addInputListener(this);
  setActivateProgram_<GLSLProgramRayTracing>();
}

GLSLProgramsManager::~GLSLProgramsManager() = default;

void GLSLProgramsManager::onWindowsResized(int x, int y)
{
  glViewport(0, 0, x, y);
  std::cout << "width: " << x << "height: " << y << std::endl;
  activeProgram_->render();
}

void GLSLProgramsManager::onMouseScrolling(int velocity)
{
  activeProgram_->onMouseScrolling(velocity);
}

template <class T>
void GLSLProgramsManager::setActivateProgram_()
{
  if (activeProgram_)
  {
    inputEventObservable_.removeMouseListener(activeProgram_.get());
  }

  activeProgram_ = std::make_unique<T>(window_);
  activeProgram_->init();
  inputEventObservable_.addInputListener(activeProgram_.get());

  int x = 0;
  int y = 0;
  SDL_GetMouseState(&x, &y);
  activeProgram_->onMouseMovePassive(x, y);
  activeProgram_->render();
}

void GLSLProgramsManager::onKeyPress(SDL_Keycode keyCode)
{
  if (keyCode == SDLK_1)
  {
    setActivateProgram_<GLSLProgramColoring>();
  }
  else if (keyCode == SDLK_2)
  {
    setActivateProgram_<GLSLProgramMandelbrot>();
  }
  else if (keyCode == SDLK_3)
  {
    setActivateProgram_<GLSLProgramRayTracing>();
  }

}
