//
//  contextProvider.h
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <memory>
#include <sdl.h>

class InputEventLogger;
class SDL_WindowWrapper;
class SDL_GLContextWrapper;
class InputEventObservable;
class PointInSquare;
class SpriteManager;
class ObjectsInitializator;


class ContextProvider
{
public:
  ContextProvider();
  ~ContextProvider();
  ContextProvider(const ContextProvider&) = delete;
  ContextProvider& operator=(const ContextProvider&) = delete;
  void notifyEvent(const SDL_Event& event) const;
  SDL_Window* getWindow() const;

private:
  std::unique_ptr<InputEventObservable> inputEventObservable_;
  std::unique_ptr<InputEventLogger> inputEventLogger_;
  std::unique_ptr<SDL_WindowWrapper> window_;
  std::unique_ptr<SDL_GLContextWrapper> context_;
  std::unique_ptr<PointInSquare> pointInSquare_;
  std::unique_ptr<SpriteManager> spriteManager_;
};