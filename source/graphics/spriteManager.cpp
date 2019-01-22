#include <glew.h>

#include "wrappers/SDL_GLContextWrapper.h"
#include "spriteManager.h"

SpriteManager::SpriteManager(SDL_Window& window) :
  window_(window),
  sprite_(Triangle2D{ Point2D(0,5), Point2D(-5, -5), Point2D(5, -5) })
{
  // It is a hack to draw everything during initialization
  onMouseMovePassive(0, 0);
  onMouseMovePassive(0, 0);
}

void SpriteManager::onMouseMovePassive(int x, int y)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shaderProgram_.use();
  sprite_.render(x, y);
  shaderProgram_.unuse();

  SDL_GL_SwapWindow(&window_);
}
