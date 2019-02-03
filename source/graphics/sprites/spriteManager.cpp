#include <glew.h>

#include <iostream>
#include <vector>
#include "wrappers/SDL_GLContextWrapper.h"
#include "observables/inputEventObservable.h"
#include "rayTracingSprite.h"
#include "spriteManager.h"

SpriteManager::SpriteManager(SDL_Window& window, InputEventObservable& inputEventObservable) :
  window_(window),
  inputEventObservable_(inputEventObservable)
{
  inputEventObservable_.addInputListener(this);
  setActivateSprite_<RayTracingSprite>();
}

void SpriteManager::onWindowsResized(int x, int y)
{
  glViewport(0, 0, x, y);
  std::cout << "width: " << x << "height: " << y << std::endl;
  activeSprite_->render();
}

void SpriteManager::onMouseScrolling(int velocity)
{
  activeSprite_->onMouseScrolling(velocity);
}

template <class T>
void SpriteManager::setActivateSprite_()
{
  if (activeSprite_)
  {
    inputEventObservable_.removeMouseListener(activeSprite_.get());
  }

  activeSprite_ = std::make_unique<T>(window_);
  activeSprite_->init();
  inputEventObservable_.addInputListener(activeSprite_.get());

  int x = 0;
  int y = 0;
  SDL_GetMouseState(&x, &y);
  activeSprite_->onMouseMovePassive(x, y);
  activeSprite_->render();
}

void SpriteManager::onKeyPress(SDL_Keycode keyCode)
{
  if (keyCode == SDLK_1)
  {
    setActivateSprite_<ColoringSprite>();
  }
  else if (keyCode == SDLK_2)
  {
    setActivateSprite_<MandelbrotSprite>();
  }
  else if (keyCode == SDLK_3)
  {
    setActivateSprite_<RayTracingSprite>();
  }

}
