//
//  mouseEventObservable.cpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#include <algorithm>

#include <sdl2/sdl.h>

#include "mouseEventListener.hpp"
#include "mouseEventObservable.hpp"

void MouseEventObservable::notifyMouseEvent(const SDL_Event& mouseEvent) const
{
  switch (mouseEvent.type)
  {
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      processMouseButton_(mouseEvent.button);
      break;
    case SDL_MOUSEMOTION:
      processMouseMotion_(mouseEvent.motion);
    default:
      //do nothing;
      break;
  }
}

void MouseEventObservable::processMouseButton_(const SDL_MouseButtonEvent& event) const
{
  if (event.button == SDL_BUTTON_LEFT)
  {
    for (auto& mouseListener: mouseEventListeners_)
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

void MouseEventObservable::processMouseMotion_(const SDL_MouseMotionEvent& event) const
{
  bool leftKeyPressed = SDL_BUTTON(SDL_GetMouseState(nullptr, nullptr)) &
    SDL_BUTTON_LMASK;
  
  for (auto& mouseListener: mouseEventListeners_)
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

void MouseEventObservable::addMouseListener(MouseEventListener* mouseListener)
{
  if (std::find(std::begin(mouseEventListeners_), std::end(mouseEventListeners_), mouseListener) ==
    std::end(mouseEventListeners_))
  {
    mouseEventListeners_.push_back(mouseListener);
  }
}

void MouseEventObservable::removeMouseListener(MouseEventListener* mouselistener)
{
  mouseEventListeners_.erase(std::remove(
    std::begin(mouseEventListeners_),
    std::end(mouseEventListeners_),
    mouselistener),
    std::end(mouseEventListeners_));
}

