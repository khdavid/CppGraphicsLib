//
//  inputListener.h
//  shaders
//
//  Created by David Khudaverdyan on 18/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <SDL.h>

class InputEventListener
{
public:
  virtual void onKeyPress(SDL_Keycode keyCode);
  virtual void onWindowsResized(int x, int y);
  virtual void onMouseClick(int x, int y);
  virtual void onMouseRelease(int x, int y);
  virtual void onMouseMove(int x, int y);
  virtual void onMouseMovePassive(int x, int y);
  virtual void onMouseScrolling(double velocity);
  virtual ~InputEventListener();
};