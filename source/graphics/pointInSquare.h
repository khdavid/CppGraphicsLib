//
//  mainScene.h
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <stdio.h>

#include "listeners/inputEventListener.h"
struct SDL_Window;

class PointInSquare : public InputEventListener
{
public:
  PointInSquare(SDL_Window& window);
  virtual void onMouseMovePassive(int x, int y) override;

private:
  SDL_Window& window_;
};
