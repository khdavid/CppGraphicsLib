//
//  mouseEventObservable.cpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#include <algorithm>
#include <sdl.h>

#include "listeners/mouseEventListener.hpp"
#include "mouseEventObservable.hpp"
#include "../eventHandlers/eventClassifier.hpp"


void MouseEventObservable::notifyMouseEvent(const SDL_Event& event) const
{
  auto type = EventClassifier::classify(event);
  switch (type)
  {
    case EventType::MouseClick:
      applyMouseEvent_(&MouseEventListener::onMouseClick, event.button);
      break;
    case EventType::MouseRelease:
      applyMouseEvent_(&MouseEventListener::onMouseRelease, event.button);
      break;
    case EventType::MouseMove:
      applyMouseEvent_(&MouseEventListener::onMouseMove, event.button);
      break;
    case EventType::MouseMovePassive:
      applyMouseEvent_(&MouseEventListener::onMouseMovePassive, event.button);
      break;
    default:
      //do nothing;
      break;
  }
}

void MouseEventObservable::applyMouseEvent_(
  void(MouseEventListener::* func)(int, int),
  const SDL_MouseButtonEvent& event) const
{
  for (auto& mouseListener : mouseEventListeners_)
  {
    (mouseListener->*func)(event.x, event.y);
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

