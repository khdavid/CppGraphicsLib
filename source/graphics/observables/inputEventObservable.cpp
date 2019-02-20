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

void InputEventObservable::notifyInputEvent(const SDL_Event& event) const
{
  auto type = EventClassifier::classify(event);
  switch (type)
  {
    case EventType::KeyDown:
    {
      for (auto& mouseListener : inputEventListeners_)
      {
        mouseListener->onKeyPress(event.key.keysym.sym);
      }
      break;
    }  
    case EventType::WindowsResized:
    {
      for (auto& mouseListener : inputEventListeners_)
      {
        mouseListener->onWindowsResized(event.window.data1, event.window.data2);
      }
      break;
    }
    case EventType::MouseScrolling:
    {
      for (auto& mouseListener : inputEventListeners_)
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
  for (auto& mouseListener : inputEventListeners_)
  {
    func(*mouseListener, event.x, event.y);
  }
}

void InputEventObservable::addInputListener(InputEventListener* inputListener)
{
  if (std::find(std::begin(inputEventListeners_), std::end(inputEventListeners_), inputListener) ==
    std::end(inputEventListeners_))
  {
    inputEventListeners_.push_back(inputListener);
  }
}

void InputEventObservable::removeInputListener(InputEventListener* inputListener)
{
  inputEventListeners_.erase(std::remove(
    std::begin(inputEventListeners_),
    std::end(inputEventListeners_),
    inputListener),
    std::end(inputEventListeners_));
}

