//
//  eventsManager.hpp
//  shaders
//
//  Created by David Khudaverdyan on 22/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef eventsManager_hpp
#define eventsManager_hpp

#include <stdio.h>
#include <sdl.h>

class EventsManager
{
public:
  static bool popEvent(SDL_Event& event, bool allowSwallowing = true);
};

#endif /* eventsManager_hpp */
