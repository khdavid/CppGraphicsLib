#include <glew.h>

#include <iostream>
#include <vector>
#include "wrappers/SDL_GLContextWrapper.h"
#include "observables/inputEventObservable.h"
#include "spriteManager.h"

namespace
{
  std::vector<Vertex> cColoringSpriteVertices =
  {
    Vertex{Position{-1.f, -1.f, 0.1f}, Material{Color{255, 0, 0}}},
    Vertex{Position{0.f, 1.f, 0.2f}, Material{Color{0, 255, 0}}},
    Vertex{Position{1.f, -1.f, 0.3f}, Material{Color{0, 0, 255}}},
    Vertex{Position{-1.f, 1.f, 0.3f}, Material{Color{0, 0, 255}}},
    Vertex{Position{0.f, -1.f, 0.2f}, Material{Color{255, 0, 0}}},
    Vertex{Position{1.f, 1.f, 0.1f}, Material{Color{0, 255, 0}}},
    Vertex{Position{-1.f, 1.f, 0.3f}, Material{Color{0, 0, 255}}},
    Vertex{Position{1.f, 0.f, 0.2f}, Material{Color{255, 0, 0}}},
    Vertex{Position{-1.f, -1.f, 0.1f}, Material{Color{0, 255, 0}}},
    Vertex{Position{1.f, 1.f, 0.1f}, Material{Color{0, 0, 255}}},
    Vertex{Position{-1.f, 0.f, 0.2f}, Material{Color{255, 0, 0}}},
    Vertex{Position{1.f, -1.f, 0.3f}, Material{Color{255, 255, 255}}}
  };

}
SpriteManager::SpriteManager(SDL_Window& window, InputEventObservable& inputEventObservable) :
  window_(window),
  inputEventObservable_(inputEventObservable)
{
  auto sprite = std::make_unique<MondelbrotSprite>(window_);
  sprite->init();
  activeSprite_ = std::move(sprite);
  activeSprite_->render();
  inputEventObservable_.addInputListener(activeSprite_.get());
  inputEventObservable_.addInputListener(this);
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

void SpriteManager::onKeyPress(SDL_Keycode keyCode)
{
  if (keyCode == SDLK_1)
  {
    inputEventObservable_.removeMouseListener(activeSprite_.get());
    activeSprite_ = nullptr;
    auto sprite = std::make_unique<ColoringSprite>(window_);
    sprite->init(cColoringSpriteVertices);
    activeSprite_ = std::move(sprite);
    inputEventObservable_.addInputListener(activeSprite_.get());
  }
  else if (keyCode == SDLK_2)
  {
    inputEventObservable_.removeMouseListener(activeSprite_.get());
    activeSprite_ = nullptr;
    auto sprite = std::make_unique<MondelbrotSprite>(window_);
    sprite->init();
    activeSprite_ = std::move(sprite);
    inputEventObservable_.addInputListener(activeSprite_.get());
  }
  int x = 0;
  int y = 0;
  SDL_GetMouseState(&x, &y);
  activeSprite_->onMouseMovePassive(x, y);
  activeSprite_->render();

}
