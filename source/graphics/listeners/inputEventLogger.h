//
//  inputEventLogger.h
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include "inputEventListener.h"

class InputEventLogger: public InputEventListener
{
public:
  virtual void onKeyPress(SDL_Keycode keyCode) override;
  virtual void onMouseRelease(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseMovePassive(int x, int y) override;
  virtual ~InputEventLogger() = default;
};
