//
//  mainLoop.h
//  shaders
//
//  Created by David Khudaverdyan on 17/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <stdio.h>

class MouseEventListener;
class ContextProvider;

class MainLoop
{
public:
  MainLoop(const ContextProvider& contextProvider);
  void run();
private:
  const ContextProvider& contextProvider_;
};