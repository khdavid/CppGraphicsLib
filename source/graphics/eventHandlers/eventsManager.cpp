//
//  eventsManager.cpp
//  shaders
//
//  Created by David Khudaverdyan on 22/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>

#include "eventClassifier.h"
#include "eventsManager.h"

namespace
{
const std::set<EventType> TYPES_TO_SWALLOW =
{
  EventType::MouseMovePassive,
  EventType::MouseMove
};

struct EventInfo
{
  SDL_Event event;
  EventType type;
  int idx;
};

std::vector<EventInfo> getKnownEventsInfo(const std::vector<SDL_Event>& events)
{
  std::vector<EventInfo> result;
  for (int i = 0; i < events.size(); ++i)
  {
    auto type = EventClassifier::classify(events[i]);
    if (type != EventType::Unknown)
    {
      result.push_back({events[i], type, i});
    }
  }
  return result;
}

std::vector<EventInfo> getFirstContiguousPart(const std::vector<EventInfo> knownEventsInfo)
{
  std::vector<EventInfo> result;
  if (knownEventsInfo.empty())
  {
    return result;
  }
  
  const auto& firstEventInfo = knownEventsInfo.front();
  for (int i = 0; i < knownEventsInfo.size(); ++i)
  {
    const auto& nextEventInfo = knownEventsInfo[i];
    if (nextEventInfo.type == firstEventInfo.type)
    {
      result.push_back(nextEventInfo);
    }
    else
    {
      break;
    }
  }
  
  return result;
}

}

bool EventsManager::popEvent(SDL_Event& event, bool allowSwallowing /* = true */)
{
  if (!allowSwallowing)
  {
    return SDL_PollEvent(&event);
  }

  SDL_PumpEvents();
  const int BUFFER_SIZE = 50;
  
  std::vector<SDL_Event> events(BUFFER_SIZE);
  const auto numEvents = SDL_PeepEvents(events.data(), BUFFER_SIZE, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
  if (numEvents < 0)
  {
    return false;
  }
  events.resize(numEvents);
  
  auto knownEventsInfo = getKnownEventsInfo(events);
  auto firstContiguousPart = getFirstContiguousPart(knownEventsInfo);
  if (firstContiguousPart.size() > 0)
  {
    auto lastElement = firstContiguousPart.back();
    if (TYPES_TO_SWALLOW.count(lastElement.type))
    {
      std::vector<SDL_Event> eventsToSwallow;
      int numEventsToSwallow = lastElement.idx;
      eventsToSwallow.reserve(numEventsToSwallow);
      SDL_PeepEvents(eventsToSwallow.data(), numEventsToSwallow, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
    }
  }
  
  return SDL_PollEvent(&event);
}

