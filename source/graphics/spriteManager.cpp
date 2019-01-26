#include <glew.h>

#include "wrappers/SDL_GLContextWrapper.h"
#include "shaders/vertexShader.h"
#include "shaders/fragmentShader.h"

#include "spriteManager.h"

SpriteManager::SpriteManager(SDL_Window& window) :
  window_(window)
{
  shaderProgram_ = std::make_unique<GLSLShaderToolBase>(cVertexShaderCode, cFragmentShaderCode);
  sprite_ = std::make_unique<TriangleSprite>(
    Triangle2D{ Point2D(0,5), Point2D(-5, -5), Point2D(5, -5) }, 
    shaderProgram_->getProgramId());
}

void SpriteManager::onMouseMovePassive(int x, int y)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  sprite_->render(x, y);

  SDL_GL_SwapWindow(&window_);
}
