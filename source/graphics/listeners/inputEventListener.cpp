//
//  inputListener.cpp
//  shaders
//
//  Created by David Khudaverdyan on 18/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include "inputEventListener.h"

void InputEventListener::onKeyPress(SDL_Keycode)
{
  //should be implemented in a child class;
}

void InputEventListener::onWindowsResized(int, int)
{
  //should be implemented in a child class;
}


void InputEventListener::onMouseRelease(int, int)
{
  //should be implemented in a child class;
}

void InputEventListener::onMouseMove(int, int)
{
  //should be implemented in a child class;
}

void InputEventListener::onMouseClickRight(int, int)
{
  //should be implemented in a child class;
}

void InputEventListener::onMouseReleaseRight(int, int)
{
  //should be implemented in a child class;
}

void InputEventListener::onMouseMoveRight(int, int)
{
  //should be implemented in a child class;
}

void InputEventListener::onMouseClick(int, int)
{
  //should be implemented in a child class;
}

void InputEventListener::onMouseMovePassive(int, int)
{
  //should be implemented in a child class;
}

void InputEventListener::onMouseScrolling(double)
{
  //should be implemented in a child class;
}

InputEventListener::~InputEventListener() = default;


