#pragma once
#include "sprites/coloringSprite.h"
#include "listeners/inputEventListener.h"
#include "GLSL/GLSLShaderCompiler.h"
#include "sprites/mandelbrotSprite.h"


struct SDL_Window;
class InputEventObservable;

class SpriteManager : public InputEventListener
{
public:
  SpriteManager(SDL_Window& window, InputEventObservable& inputEventObservable);

  virtual void onKeyPress(SDL_Keycode keyCode) override;
  virtual void onWindowsResized(int, int) override;
  virtual void onMouseScrolling(int) override;

private:
  template <class T>
  void setActivateSprite_();

  SDL_Window& window_;
  InputEventObservable& inputEventObservable_;
  std::unique_ptr<SpriteBase> activeSprite_;
};

