//
//  mouseEventObservable.h
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <vector>
#include <functional>

class InputEventListener;
struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;
union SDL_Event;

class InputEventObservable
{
public:
  InputEventObservable(const InputEventObservable&) = delete;
  InputEventObservable() = default;
  void addInputListener(InputEventListener* mouselistener);
  void removeMouseListener(InputEventListener* mouselistener);
  void notifyMouseEvent(const SDL_Event& mouseEvent) const;
private:
  void applyMouseEvent_(std::function<void(InputEventListener&, int, int)> func,
    const SDL_MouseButtonEvent&) const;
  void onMouseClick_(const SDL_MouseButtonEvent& mouseEvent) const;
  void onMouseRelease_(const SDL_MouseButtonEvent& mouseEvent) const;
  void onMouseMove_(const SDL_MouseMotionEvent& mouseEvent) const;
  void onMouseMovePassive_(const SDL_MouseMotionEvent& mouseEvent) const;

  std::vector<InputEventListener*> mouseEventListeners_;
};