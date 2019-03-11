//
//  mouseEventObservable.h
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <functional>
#include <map>
#include <sdl.h>

class InputEventListener;
struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;
union SDL_Event;

class InputEventObservable
{
public:
  InputEventObservable(const InputEventObservable&) = delete;
  InputEventObservable() = default;
  void addInputListener(InputEventListener* inputListener);
  void removeInputListener(InputEventListener* inputListener);
  void notifyInputEvent(const SDL_Event& inputEvent);
private:
  void applyMouseEvent_(std::function<void(InputEventListener&, int, int)> func,
    const SDL_MouseButtonEvent&);
  void onMouseClick_(const SDL_MouseButtonEvent& mouseEvent);
  void onMouseRelease_(const SDL_MouseButtonEvent& mouseEvent);
  void onMouseMove_(const SDL_MouseMotionEvent& mouseEvent);
  void onMouseMovePassive_(const SDL_MouseMotionEvent& mouseEvent);

  size_t findMinNonExistedKey_() const;

  //we use the keys here to ensure the determenistic order of listeners
  std::map<size_t, InputEventListener*> inputEventListeners_;
  Uint32 scrollingTimeOld_ = 0;
};