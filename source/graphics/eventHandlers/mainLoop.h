//
//  mainLoop.h
//  shaders
//
//  Created by David Khudaverdyan on 17/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

class InputEventListener;
class ContextManager;

class MainLoop
{
public:
  MainLoop(const ContextManager& contextProvider);
  void run();
private:
  const ContextManager& contextProvider_;
};