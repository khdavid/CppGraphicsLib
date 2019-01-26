#include <glew.h>

#include "wrappers/SDL_GLContextWrapper.h"

#include "spriteManager.h"

SpriteManager::SpriteManager(SDL_Window& window) :
  window_(window)
{
  sprite_.init();
  onMouseMovePassive(0,0);
}

void SpriteManager::onMouseMovePassive(int x, int y)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  sprite_.render(x, y);

  SDL_GL_SwapWindow(&window_);
}
