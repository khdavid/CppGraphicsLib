//
//  mouseEventObservable.cpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#include <algorithm>
#include <sdl.h>
#include <iostream>

#include "listeners/inputEventListener.h"
#include "inputEventObservable.h"
#include "../eventHandlers/eventClassifier.h"

void InputEventObservable::notifyInputEvent(const SDL_Event& event)
{
  auto type = EventClassifier::classify(event);
  switch (type)
  {
    case EventType::KeyDown:
    {
      for (auto& inputEventListener : inputEventListeners_)
      {
        inputEventListener.second->onKeyPress(event.key.keysym.sym);
      }
      break;
    }  
    case EventType::WindowsResized:
    {
      for (auto& inputEventListener : inputEventListeners_)
      {
        inputEventListener.second->onWindowsResized(event.window.data1, event.window.data2);
      }
      break;
    }
    case EventType::MouseScrolling:
      applyMouseScrolling_(event.wheel);
      break;
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
  const SDL_MouseButtonEvent& event) 
{
  for (auto& mouseListener : inputEventListeners_)
  {
    func(*mouseListener.second, event.x, event.y);
  }
}

void InputEventObservable::applyMouseScrolling_(const SDL_MouseWheelEvent& wheel)
{
  auto time = wheel.timestamp;
  int dt = time - scrollingTimeOld_;
  auto ySign = (wheel.y > 0) ? 1 : -1;
  if (ySign != 0)
  {
    scrollingSign_ = ySign;
  }

  const int cTimeDelta = 100;
  const int cMinDelta = 10;
  const double SCROLLING_FACTOR = 3.0;

  dt = dt < cTimeDelta ? dt : cMinDelta;
  std::cout << "dt: " << dt << std::endl;
  for (auto& inputEventListener : inputEventListeners_)
  {
    double speed = (scrollingSign_ * dt / SCROLLING_FACTOR);
    inputEventListener.second->onMouseScrolling(speed);
  }
  scrollingTimeOld_ = time;
}

size_t InputEventObservable::findMinNonExistedKey_() const
{
  size_t result = 0;

  for (const auto& pair : inputEventListeners_)
  {
    if (pair.first != result)
    {
      return result;
    }
    result++;
  }

  return result;
}

void InputEventObservable::addInputListener(InputEventListener* inputListener)
{
  inputEventListeners_.emplace(findMinNonExistedKey_(), inputListener );
}

void InputEventObservable::removeInputListener(InputEventListener* inputListener)
{
  for (auto& pair : inputEventListeners_)
  {
    if (pair.second == inputListener)
    {
      inputEventListeners_.erase(pair.first);
      return;
    }
  }
}

