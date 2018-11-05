//
//  mainScene.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <sdl_opengl.h>
#include <sdl.h>
#include "pointInSquare.hpp"

PointInSquare::PointInSquare(SDL_Window& window):
  window_(window)
{
}

void PointInSquare::onMouseClick(int x, int y)
{

}
void PointInSquare::onMouseRelease(int x, int y)
{

}
void PointInSquare::onMouseMove(int x, int y)
{

}

void PointInSquare::onMouseMovePassive(int x, int y)
{
  int xMax, yMax;
  SDL_GetWindowSize(&window_, &xMax, &yMax);
  float xMouse = (float) x / (0.5 * xMax) - 1.0;
  float yMouse = 1.0 - (float) y / (0.5 * yMax);

  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnableClientState(GL_COLOR_ARRAY);
  glBegin(GL_TRIANGLES);

    glColor3f(0, 1, 0);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(xMouse, yMouse);

    glColor3f(1, 1, 0);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(xMouse, yMouse);

    glColor3f(0, 0, 1);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glVertex2f(xMouse, yMouse);

    glColor3f(1, 0, 0);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(xMouse, yMouse);

///////////////////////////

    glColor3f(1, 0, 0);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(xMouse, yMouse);

    glColor3f(0, 1, 1);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(xMouse, yMouse);

    glColor3f(1, 1, 0);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(xMouse, yMouse);

    glColor3f(0, 0, 1);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(xMouse, yMouse);

  glEnd();
  SDL_GL_SwapWindow(&window_);
}

