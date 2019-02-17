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
#include "object/objectsInitializator.h"
#include "rayTracingContextProvider.h"

#include "contextManager.h"

ContextManager::ContextManager()
{
  inputEventObservable_ = std::make_unique<InputEventObservable>();
  window_ = std::make_unique<SDL_WindowWrapper>();
  context_ = std::make_unique<SDL_GLContextWrapper>(window_->getNative());
  inputEventLogger_ = std::make_unique<InputEventLogger>();
  objectsInitializator_ = std::make_unique<ObjectsInitializator>();
  inputEventObservable_->addInputListener(inputEventLogger_.get());
  activeContextProvider_ = std::make_unique<RayTracingContextProvider>(*window_, *inputEventObservable_);
}

void ContextManager::notifyEvent(const SDL_Event& event) const
{
  inputEventObservable_->notifyMouseEvent(event);
}

SDL_Window* ContextManager::getWindow() const
{
  return window_->getNative();
}



ContextManager::~ContextManager() = default;

