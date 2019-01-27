#include <glew.h>

#include <vector>
#include "wrappers/SDL_GLContextWrapper.h"
#include "spriteManager.h"

namespace
{
  std::vector<Vertex> cColoringSpriteVertices =
  {
    Vertex{Position{-1, -1, 0.1}, Material{Color{255, 0, 0}}},
    Vertex{Position{0, 1, 0.2}, Material{Color{0, 255, 0}}},
    Vertex{Position{1, -1, 0.3}, Material{Color{0, 0, 255}}},
    Vertex{Position{-1, 1, 0.3}, Material{Color{0, 0, 255}}},
    Vertex{Position{0, -1, 0.2}, Material{Color{255, 0, 0}}},
    Vertex{Position{1, 1, 0.1}, Material{Color{0, 255, 0}}},
    Vertex{Position{-1, 1, 0.3}, Material{Color{0, 0, 255}}},
    Vertex{Position{1, 0, 0.2}, Material{Color{255, 0, 0}}},
    Vertex{Position{-1, -1, 0.1}, Material{Color{0, 255, 0}}},
    Vertex{Position{1, 1, 0.1}, Material{Color{0, 0, 255}}},
    Vertex{Position{-1, 0, 0.2}, Material{Color{255, 0, 0}}},
    Vertex{Position{1, -1, 0.3}, Material{Color{255, 255, 255}}}
  };

}
SpriteManager::SpriteManager(SDL_Window& window) :
  window_(window)
{
  activeSprite_ = std::make_unique<MondelbrotSprite>();
  onMouseMovePassive(0,0);
}

void SpriteManager::onMouseMovePassive(int x, int y)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  static size_t itr = 0;
  itr++;
  
  if ((itr % 10) == 1 )
  {
    activeSprite_ = nullptr;
    auto sprite = std::make_unique<ColoringSprite>();
    sprite->init(cColoringSpriteVertices);
    activeSprite_ = std::move(sprite);
  }
  else if ((itr % 10) == 5)
  {
    activeSprite_ = nullptr;
    auto sprite = std::make_unique<MondelbrotSprite>();
    sprite->init();
    activeSprite_ = std::move(sprite);
  }
  activeSprite_->render(x, y);

  SDL_GL_SwapWindow(&window_);
}
