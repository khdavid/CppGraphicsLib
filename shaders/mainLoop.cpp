//
//  mainLoop.cpp
//  shaders
//
//  Created by David Khudaverdyan on 17/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#include <algorithm>

#include <sdl2/sdl.h>

#include "listeners/mouseListener.hpp"
#include "mainLoop.hpp"

bool MainLoop::run()
{
  SDL_Event e;
  
  bool quit = false;
  while (!quit)
  {
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
          processMouseButton_(e.button);
          break;
        case SDL_MOUSEMOTION:
          processMouseMotion_(e.motion);
      }
    }
  }
  return true;
}

void MainLoop::processMouseButton_(const SDL_MouseButtonEvent& event)
{
  if (event.button == SDL_BUTTON_LEFT)
  {
    for (auto& mouseListener: mouseListeners_)
    {
      if (event.state == SDL_PRESSED)
      {
        mouseListener->onMouseClick();
      }
      else
      {
        mouseListener->onMouseRelease();
      }
    }
  }
}

void MainLoop::processMouseMotion_(const SDL_MouseMotionEvent& event)
{
  bool leftKeyPressed = SDL_BUTTON(SDL_GetMouseState(nullptr, nullptr)) &
    SDL_BUTTON_LMASK;
  
  for (auto& mouseListener: mouseListeners_)
  {
    if (leftKeyPressed)
    {
      mouseListener->onMouseMove(event.x, event.y);
    }
    else
    {
      mouseListener->onMouseMovePassive(event.x, event.y);
    }
}
}


void MainLoop::addMouseListener(MouseListener* mouseListener)
{
  if (std::find(std::begin(mouseListeners_), std::end(mouseListeners_), mouseListener) ==
    std::end(mouseListeners_))
  {
    mouseListeners_.push_back(mouseListener);
  }
}

void MainLoop::removeMouseListener(MouseListener* mouselistener)
{
  mouseListeners_.erase(std::remove(
    std::begin(mouseListeners_),
    std::end(mouseListeners_),
    mouselistener),
    std::end(mouseListeners_));
}





