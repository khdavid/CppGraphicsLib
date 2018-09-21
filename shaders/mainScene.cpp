//
//  mainScene.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <opengl/gl.h>
#include <sdl2/sdl.h>
#include "mainScene.hpp"

MainScene::MainScene(SDL_Window& window):
  window_(window)
{
}

void MainScene::onMouseClick(int x, int y)
{

}
void MainScene::onMouseRelease(int x, int y)
{

}
void MainScene::onMouseMove(int x, int y)
{

}
void MainScene::onMouseMovePassive(int x, int y)
{
  float xf = x;
  float yf = y;
  int xMax, yMax;
  SDL_GetWindowSize(&window_, &xMax, &yMax);
  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnableClientState(GL_COLOR_ARRAY);
  glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0, 0);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(xf / (0.5 * xMax) - 1.0, 1.0 - yf / (0.5 * yMax));
  glEnd();
  SDL_GL_SwapWindow(&window_);
}

