//
//  eventClassifier.h
//  shaders
//
//  Created by David Khudaverdyan on 21/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef eventClassifier_hpp
#define eventClassifier_hpp

#include <stdio.h>
#include <sdl.h>

enum class EventType
{
  MouseClick,
  MouseRelease,
  MouseMove,
  MouseMovePassive,
  Unknown
};

class EventClassifier
{
public:
  static EventType classify(const SDL_Event& event);
};

#endif /* eventClassifier_hpp */
