//
//  contextProvider.h
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//
#pragma once

#include <memory>
#include <sdl.h>

#include "listeners/inputEventListener.h"

class InputEventLogger;
class SDL_WindowWrapper;
class SDL_GLContextWrapper;
class InputEventObservable;
class GLSLProgramsManager;
class ContextProvider;


class ContextManager : public InputEventListener
{
public:
  ContextManager();
  ~ContextManager();
  ContextManager(const ContextManager&) = delete;
  ContextManager& operator=(const ContextManager&) = delete;
  void notifyEvent(const SDL_Event& event) const;
  SDL_Window* getWindow() const;
  virtual void onKeyPress(SDL_Keycode keyCode) override;

  std::unique_ptr<SDL_WindowWrapper> window_;
  std::unique_ptr<InputEventObservable> inputEventObservable_;
  std::unique_ptr<InputEventLogger> inputEventLogger_;
  std::unique_ptr<SDL_GLContextWrapper> context_;
  std::unique_ptr<ContextProvider> activeContextProvider_;
};