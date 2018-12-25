#include <glew.h>

#include "wrappers/SDL_GLContextWrapper.h"
#include "spriteManager.h"

SpriteManager::SpriteManager(SDL_Window& window) :
  window_(window),
  sprite_(Triangle2D{ Point2D(0,0), Point2D(-1, -1), Point2D(1, -1) })
{
  // It is a hack to draw everything during initialization
  onMouseMovePassive(0, 0);
  onMouseMovePassive(0, 0);
}

void SpriteManager::onMouseMovePassive(int x, int y)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  shaderProgram_.use();
  sprite_.render(x, y);
  shaderProgram_.unuse();

  SDL_GL_SwapWindow(&window_);
}
