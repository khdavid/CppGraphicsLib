//
//  mouseEventObservable.cpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#include <algorithm>
#include <sdl.h>

#include "listeners/inputEventListener.h"
#include "inputEventObservable.h"
#include "../eventHandlers/eventClassifier.h"

void InputEventObservable::notifyMouseEvent(const SDL_Event& event) const
{
  auto type = EventClassifier::classify(event);
  switch (type)
  {
    case EventType::KeyDown:
    {
      for (auto& mouseListener : mouseEventListeners_)
      {
        mouseListener->onKeyPress(event.key.keysym.sym);
      }
      break;
    }  
    case EventType::WindowsResized:
    {
      for (auto& mouseListener : mouseEventListeners_)
      {
        mouseListener->onWindowsResized(event.window.data1, event.window.data2);
      }
      break;
    }
    case EventType::MouseScrolling:
    {
      for (auto& mouseListener : mouseEventListeners_)
      {
        mouseListener->onMouseScrolling(event.wheel.y);
      }
      break;
    }

    case EventType::MouseClick:
      applyMouseEvent_(&InputEventListener::onMouseClick, event.button);
      break;
    case EventType::MouseRelease:
      applyMouseEvent_(&InputEventListener::onMouseRelease, event.button);
      break;
    case EventType::MouseMove:
      applyMouseEvent_(&InputEventListener::onMouseMove, event.button);
      break;
    case EventType::MouseMovePassive:
      applyMouseEvent_(&InputEventListener::onMouseMovePassive, event.button);
      break;
    default:
      //do nothing;
      break;
  }
}

void InputEventObservable::applyMouseEvent_(
  std::function<void(InputEventListener&, int, int)> func,
  const SDL_MouseButtonEvent& event) const
{
  for (auto& mouseListener : mouseEventListeners_)
  {
    func(*mouseListener, event.x, event.y);
  }
}

void InputEventObservable::addInputListener(InputEventListener* mouseListener)
{
  if (std::find(std::begin(mouseEventListeners_), std::end(mouseEventListeners_), mouseListener) ==
    std::end(mouseEventListeners_))
  {
    mouseEventListeners_.push_back(mouseListener);
  }
}

void InputEventObservable::removeMouseListener(InputEventListener* mouselistener)
{
  mouseEventListeners_.erase(std::remove(
    std::begin(mouseEventListeners_),
    std::end(mouseEventListeners_),
    mouselistener),
    std::end(mouseEventListeners_));
}

