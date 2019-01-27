//
//  mouseEventObservable.h
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <vector>
#include <functional>

class MouseEventListener;
class SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;
union SDL_Event;

class MouseEventObservable
{
public:
  MouseEventObservable(const MouseEventObservable&) = delete;
  MouseEventObservable() = default;
  void addMouseListener(MouseEventListener* mouselistener);
  void removeMouseListener(MouseEventListener* mouselistener);
  void notifyMouseEvent(const SDL_Event& mouseEvent) const;
private:
  void applyMouseEvent_(std::function<void(MouseEventListener&, int, int)> func,
    const SDL_MouseButtonEvent&) const;
  void onMouseClick_(const SDL_MouseButtonEvent& mouseEvent) const;
  void onMouseRelease_(const SDL_MouseButtonEvent& mouseEvent) const;
  void onMouseMove_(const SDL_MouseMotionEvent& mouseEvent) const;
  void onMouseMovePassive_(const SDL_MouseMotionEvent& mouseEvent) const;

  std::vector<MouseEventListener*> mouseEventListeners_;
};