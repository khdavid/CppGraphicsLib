//
//  contextProvider.cpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <sdl.h>
 
#include "listeners/inputEventLogger.h"
#include "wrappers/SDL_WindowWrapper.h"
#include "wrappers/SDL_GLContextWrapper.h"
#include "observables/inputEventObservable.h"
#include "rayTracingContextProvider.h"
#include "mandelbrotContextProvider.h"
#include "coloringContextProvider.h"

#include "contextManager.h"

ContextManager::ContextManager()
{
  inputEventObservable_ = std::make_unique<InputEventObservable>();
  window_ = std::make_unique<SDL_WindowWrapper>();
  context_ = std::make_unique<SDL_GLContextWrapper>(window_->getNative());
  inputEventLogger_ = std::make_unique<InputEventLogger>();
  inputEventObservable_->addInputListener(inputEventLogger_.get());
  inputEventObservable_->addInputListener(this);
  activeContextProvider_ = std::make_unique<RayTracingContextProvider>(*window_->getNative(), *inputEventObservable_);
}

void ContextManager::notifyEvent(const SDL_Event& event) const
{
  inputEventObservable_->notifyInputEvent(event);
}

SDL_Window* ContextManager::getWindow() const
{
  return window_->getNative();
}

void ContextManager::onKeyPress(SDL_Keycode keyCode)
{
  if (keyCode == SDLK_1)
  {
    activeContextProvider_ = nullptr;
    activeContextProvider_ = std::make_unique<RayTracingContextProvider>(*window_->getNative(), *inputEventObservable_);
  }
  else if (keyCode == SDLK_2)
  {
    activeContextProvider_ = nullptr;
    activeContextProvider_ = std::make_unique<MandelbrotContextProvider>(*window_->getNative(), *inputEventObservable_);
  }
  else if (keyCode == SDLK_3)
  {
    activeContextProvider_ = nullptr;
    activeContextProvider_ = std::make_unique<ColoringContextProvider>(*window_->getNative(), *inputEventObservable_);
  }

}

ContextManager::~ContextManager() = default;

