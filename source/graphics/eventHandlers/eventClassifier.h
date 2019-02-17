//
//  eventClassifier.h
//  shaders
//
//  Created by David Khudaverdyan on 21/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <sdl.h>

enum class EventType
{
  MouseClick,
  MouseRelease,
  MouseMove,
  MouseMovePassive,
  MouseScrolling,
  KeyDown,
  WindowsResized,
  Unknown
};

class EventClassifier
{
public:
  static EventType classify(const SDL_Event& event);
};