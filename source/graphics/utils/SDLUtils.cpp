#include <SDL.h>
#include <glew.h>
#include "SDLUtils.h"


namespace SDLUtils
{
std::pair<int, int> getMouseXY()
{
  int x = 0;
  int y = 0;
  SDL_GetMouseState(&x, &y);
  return { x, y };
}

Point2DInt getScreenSizes()
{
  GLint m_viewport[4];

  glGetIntegerv(GL_VIEWPORT, m_viewport);
  return Point2DInt( m_viewport[2], m_viewport[3] );
}

} //end of namespace SDLUtils
