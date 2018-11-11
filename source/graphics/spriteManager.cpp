#include <glew.h>

#include "wrappers/SDL_GLContextWrapper.h"
#include "spriteManager.h"

SpriteManager::SpriteManager(SDL_Window& window) :
  window_(window),
  sprite_(Triangle2D{ Point2D(0,0), Point2D(0, 0.3), Point2D(0.3, 0.4) })
{

}

void SpriteManager::onMouseMovePassive(int x, int y)
{
  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnableClientState(GL_COLOR_ARRAY);
  sprite_.draw();

  SDL_GL_SwapWindow(&window_);
}
