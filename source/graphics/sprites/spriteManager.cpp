#include <glew.h>

#include <iostream>
#include <vector>
#include "wrappers/SDL_GLContextWrapper.h"
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
SpriteManager::SpriteManager(SDL_Window& window) :
  window_(window)
{
  auto sprite = std::make_unique<MondelbrotSprite>();
  sprite->init();
  activeSprite_ = std::move(sprite);
  onMouseMovePassive(0,0);
}

void SpriteManager::onMouseMovePassive(int x, int y)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  activeSprite_->render(x, y);

  SDL_GL_SwapWindow(&window_);
}

void SpriteManager::onMouseMove(int x, int y)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  activeSprite_->onMouseMove(x, y);
  SDL_GL_SwapWindow(&window_);
}

void SpriteManager::onMouseClick(int x, int y)
{
  activeSprite_->onMouseClick(x, y);
}

void SpriteManager::onMouseRelease(int x, int y)
{
  activeSprite_->onMouseRelease(x, y);
}

void SpriteManager::onWindowsResized(int x, int y)
{
  glViewport(0, 0, x, y);
  std::cout << "width: " << x << "height: " << y << std::endl;
}

void SpriteManager::onMouseScrolling(int velocity)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  activeSprite_->onMouseScrolling(velocity);
  SDL_GL_SwapWindow(&window_);

}

void SpriteManager::onKeyPress(SDL_Keycode keyCode)
{
  if (keyCode == SDLK_1)
  {
    activeSprite_ = nullptr;
    auto sprite = std::make_unique<ColoringSprite>();
    sprite->init(cColoringSpriteVertices);
    activeSprite_ = std::move(sprite);
  }
  else if (keyCode == SDLK_2)
  {
    activeSprite_ = nullptr;
    auto sprite = std::make_unique<MondelbrotSprite>();
    sprite->init();
    activeSprite_ = std::move(sprite);
  }
  int x = 0;
  int y = 0;
  SDL_GetMouseState(&x, &y);
  onMouseMovePassive(x, y);
}
