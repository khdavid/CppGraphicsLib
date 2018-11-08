//
//  eventClassifier.cpp
//  shaders
//
//  Created by David Khudaverdyan on 21/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include "eventClassifier.h"

namespace
{
EventType classifyMouseButton(const SDL_MouseButtonEvent& event)
{
  if (event.button == SDL_BUTTON_LEFT)
  {
    if (event.state == SDL_PRESSED)
    {
      return EventType::MouseClick;
    }
    else
    {
      return EventType::MouseRelease;
    }
  }
  return EventType::Unknown;
}

EventType classifyMouseMotion(const SDL_MouseMotionEvent& event)
{
  bool leftKeyPressed = SDL_BUTTON(SDL_GetMouseState(nullptr, nullptr)) &
    SDL_BUTTON_LMASK;
  
  if (leftKeyPressed)
  {
    return EventType::MouseMove;
  }
  else
  {
    return EventType::MouseMovePassive;
  }
  return EventType::Unknown;
}
}
EventType EventClassifier::classify(const SDL_Event& event)
{
  switch (event.type)
  {
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      return classifyMouseButton(event.button);
    case SDL_MOUSEMOTION:
      return classifyMouseMotion(event.motion);
    default:
      return EventType::Unknown;
  }
}

