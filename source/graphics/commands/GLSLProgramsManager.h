#pragma once
#include "GLSL/GLSLProgramColoring.h"
#include "listeners/inputEventListener.h"
#include "GLSL/GLSLShaderCompiler.h"
#include "GLSL/GLSLProgramMandelbrot.h"


struct SDL_Window;
class InputEventObservable;

class GLSLProgramsManager : public InputEventListener
{
public:
  GLSLProgramsManager(SDL_Window& window, InputEventObservable& inputEventObservable);

  virtual void onKeyPress(SDL_Keycode keyCode) override;
  virtual void onWindowsResized(int, int) override;
  virtual void onMouseScrolling(int) override;

private:
  template <class T>
  void setActivateProgram_();

  SDL_Window& window_;
  InputEventObservable& inputEventObservable_;
  std::unique_ptr<GLSLProgramBase> activeProgram_;
};

