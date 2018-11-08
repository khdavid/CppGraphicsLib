//
//  eventsManager.h
//  shaders
//
//  Created by David Khudaverdyan on 22/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <sdl.h>

class EventsManager
{
public:
  static bool popEvent(SDL_Event& event, bool allowSwallowing = true);
};